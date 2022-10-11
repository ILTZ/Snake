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

}

void HUD::DrawHUD(sf::RenderWindow& _wnd)
{
	_wnd.draw(*hudSprite);
	drawWidgets(_wnd);
}

void Hud::HUD::DrawButtons(sf::RenderWindow& _wnd)
{
	std::lock_guard<std::mutex> lk(defMutex);

	for (size_t i = 0; i < btns.size(); ++i)
	{
		btns[i]->Draw(_wnd);
	}
}

void Hud::HUD::SetScale(const sf::Vector2f& _newScale)
{
	currentScale = _newScale;
	hudSprite->setScale(currentScale);
}

const sf::Vector2u Hud::HUD::GetHUDSize() const
{
	return hud->getSize();
}

const sf::Vector2f Hud::HUD::GetHudPosition() const
{
	return hudPos;
}

void Hud::HUD::SetHudPosition(const sf::Vector2f& _newPos)
{
	hudPos = _newPos;
	hudSprite->setPosition(hudPos);
}

const sf::Vector2f Hud::HUD::GetButtonsPosition() const
{
	return buttonsPos;
}

void Hud::HUD::SetButtonsPosition(const sf::Vector2f& _newPos)
{
	buttonsPos = _newPos;

	for (size_t i = 0; i < btns.size(); ++i)
	{
		btns[i]->SetPosition(sf::Vector2f(
			buttonsPos.x,
			(buttonsPos.y / static_cast<float>(btns.size() + 2)) * static_cast<float>(i + 1)));
	}
}

std::optional <Buttons::BtnPurpose> Hud::HUD::CheckButtonsTouch(float _x, float _y)
{
	for (size_t i = 0; i < btns.size(); ++i)
	{
		if (btns[i]->GetTouch(_x, _y))
		{
			return btns[i]->GetBtnPurpose();
		}
	}

	return {};
}

void Hud::HUD::AddWidget(std::shared_ptr<InfoWidget> _widget)
{
	assert(widgetArr.size() != baseWidgetArraySize);

	widgetArr.emplace_back(_widget);
	widgetArr.back()->SetScale(currentScale);

	for (size_t i = 0; i < widgetArr.size(); ++i)
	{
		widgetArr[i]->SetPosition(
			sf::Vector2f(
				hudPos.x + hudSprite->getGlobalBounds().width / 2.f,
				(buttonsPos.y / static_cast<float>(widgetArr.size() + 1)) * static_cast<float>(i + 1)));
	}
}

void Hud::HUD::ClearWidgets()
{
	widgetArr.clear();
}

void Hud::HUD::RealeseButtons()
{
	for (auto& el : btns)
	{
		el->SetState(Buttons::BtnState::RELEASED);
	}
}

void Hud::HUD::PrepButtons(APP_STATE::States _state, int _lvlCount)
{
	std::lock_guard<std::mutex> lock(defMutex);

	btns.clear();

	switch (_state)
	{
		case APP_STATE::States::MAIN_MENU:
		{
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::START, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Start"));
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::LEADER_BORD, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Leaderbord"));
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
		}
		break;

		case APP_STATE::States::LVL_SELECT:
		{
			assert(_lvlCount);

			Buttons::BtnPurpose tempB = Buttons::BtnPurpose::LVL_1;
			for (int i = 0; i < _lvlCount; ++i)
			{
				btns.emplace_back(new Buttons::Button(tempB, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(),
					(std::string("LVL ") + std::to_string(i + 1)).c_str()
				));
				++tempB;
			}
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Back"));
		}
		break;

		case APP_STATE::States::LEADERS_VIEW:
		{
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Back"));
		}
		break;

		case APP_STATE::States::GAME_PAUSE:
		{
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::CONTINUE, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Continue"));
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Main Menu"));
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
		}
		break;

		case APP_STATE::States::GAME_OVER:
		{
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Main Menu"));
			btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
		}
		break;

		default:
			break;
	}

	for (auto& el : btns)
	{
		el->SetScale(currentScale);
	}

	for (size_t i = 0; i < btns.size(); ++i)
	{
		btns[i]->SetPosition(sf::Vector2f(
			buttonsPos.x,
			(buttonsPos.y / static_cast<float>(btns.size() + 2)) * static_cast<float>(i + 1)));
	}
}

void Hud::HUD::drawWidgets(sf::RenderWindow& _wnd)
{
	for (size_t i = 0; i < widgetArr.size(); ++i)
	{
		widgetArr[i]->Draw(_wnd);
	}
}


