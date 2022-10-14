#include "HUD.h"

#include <cassert>

using namespace Hud;

HUD::HUD(
	const char* _pathToHud, 
	const char* _pathToBtnReleased, 
	const char* _pathToBtnPressed, 
	const char* _pathToFont) :
	pathToHUD				{_pathToHud}, 
	pathToBtnReleased		{_pathToBtnReleased}, 
	pathToBtnPressed		{_pathToBtnPressed}, 
	pathToFont				{_pathToFont},
	hud						{new sf::Texture()},
	currentScale			{1.f,1.f}
{
	hud->loadFromFile(pathToHUD.c_str());
	hudSprite = new sf::Sprite(*hud);


	const sf::Vector2f wnd(1200.f, 800.f);

	btnsLayout = new LAYOUT::Layout(wnd / 2.f, wnd / 4.f);
}

Hud::HUD::HUD(CLoader::HudConfigs& _configs) :
	pathToBtnReleased{_configs.pathToReleaseBtn},
	pathToBtnPressed{_configs.pathToPressBtn},
	pathToFont{_configs.pathToTextFont},
	hud{new sf::Texture()},
	currentScale{1.f,1.f}
{
	hud->loadFromFile(_configs.pathToHud);
	hudSprite = new sf::Sprite(*hud);

	const sf::Vector2f wndSize(
		static_cast<float>(_configs.width),
		static_cast<float>(_configs.height));

	btnsLayout = new LAYOUT::Layout(wndSize, wndSize / 2.f);
}

void HUD::DrawHUD(sf::RenderWindow& _wnd)
{
	_wnd.draw(*hudSprite);
	drawWidgets(_wnd);
}

void Hud::HUD::DrawButtons(sf::RenderWindow& _wnd)
{
	std::lock_guard<std::mutex> lk(defMutex);

	btnsLayout->Draw(_wnd);
}

void Hud::HUD::SetScale(const sf::Vector2f& _newScale)
{
	currentScale = _newScale;
	hudSprite->setScale(currentScale);
	btnsLayout->SetScale(currentScale);
}

const sf::Vector2u Hud::HUD::GetHUDSize() const
{
	return hud->getSize();
}

const sf::Vector2f Hud::HUD::GetHudSpritePosition() const
{
	return hudSprite->getPosition();
}

void Hud::HUD::SetHudSpritePosition(const sf::Vector2f& _newPos)
{
	hudSprite->setPosition(_newPos);
}

const sf::Vector2f Hud::HUD::GetButtonsPosition() const
{
	return buttonsPos;
}

void Hud::HUD::SetButtonsPosition(const sf::Vector2f& _newPos)
{
	buttonsPos = _newPos;
	btnsLayout->SetPosition(_newPos);
}

std::optional <Buttons::BtnPurpose> Hud::HUD::CheckButtonsTouch(float _x, float _y)
{
	for (size_t i = 0; i < btnsLogicArr.size(); ++i)
	{
		if (btnsLogicArr[i]->GetTouch(_x, _y))
		{
			return btnsLogicArr[i]->GetBtnPurpose();
		}
	}

	return {};
}

void Hud::HUD::AddWidget(std::shared_ptr<BaseDrawable> _widget)
{
	assert(widgetArr.size() != baseWidgetArraySize);

	widgetArr.emplace_back(_widget);
	widgetArr.back()->SetScale(currentScale);

	for (size_t i = 0; i < widgetArr.size(); ++i)
	{
		widgetArr[i]->SetPosition(
			sf::Vector2f(
				hudSprite->getPosition().x + hudSprite->getGlobalBounds().width / 2.f,
				(buttonsPos.y / static_cast<float>(widgetArr.size() + 1)) * static_cast<float>(i + 1)));
	}
}

void Hud::HUD::ClearWidgets()
{
	widgetArr.clear();
}

void Hud::HUD::RealeseButtons()
{
	for (auto& el : btnsLogicArr)
	{
		el->SetState(Buttons::BtnState::RELEASED);
	}
}

void Hud::HUD::PrepButtons(APP_STATE::States _state, int _lvlCount)
{
	std::lock_guard<std::mutex> lock(defMutex);

	btnsLogicArr.clear();
	btnsLayout->ClearLayout();

	switch (_state)
	{
		case APP_STATE::States::MAIN_MENU:
		{
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::START, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Start"));
			btnsLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::LEADER_BORD, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Leaderbord"));
			btnsLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
			btnsLayout->AddObject(btnsLogicArr.back());

		}
		break;

		case APP_STATE::States::LVL_SELECT:
		{
			assert(_lvlCount);

			Buttons::BtnPurpose tempB = Buttons::BtnPurpose::LVL_1;
			for (int i = 0; i < _lvlCount; ++i)
			{
				btnsLogicArr.emplace_back(new Buttons::Button(tempB, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(),
					(std::string("LVL ") + std::to_string(i + 1)).c_str()
				));
				++tempB;

				btnsLayout->AddObject(btnsLogicArr.back());
			}
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Back"));
			btnsLayout->AddObject(btnsLogicArr.back());
		}
		break;

		case APP_STATE::States::LEADERS_VIEW:
		{
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Back"));
			btnsLayout->AddObject(btnsLogicArr.back());
		}
		break;

		case APP_STATE::States::GAME_PAUSE:
		{
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::CONTINUE, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Continue"));
			btnsLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Main Menu"));
			btnsLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
			btnsLayout->AddObject(btnsLogicArr.back());
		}
		break;

		case APP_STATE::States::GAME_OVER:
		{
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Main Menu"));
			btnsLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
			btnsLayout->AddObject(btnsLogicArr.back());
		}
		break;

		default:
			break;
	}

	//btnsLayout->SetScale(currentScale);

}

void Hud::HUD::drawWidgets(sf::RenderWindow& _wnd)
{
	for (size_t i = 0; i < widgetArr.size(); ++i)
	{
		widgetArr[i]->Draw(_wnd);
	}
}


