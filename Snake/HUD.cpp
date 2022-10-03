#include "HUD.h"

#include <cassert>

using namespace Hud;

HUD::HUD(
	const char* _pathToHud, 
	const char* _pathToBtnReleased, 
	const char* _pathToBtnPressed, 
	const char* _pathToFont,
	const sf::Vector2u& _wndSize) :
	pathToHUD				{_pathToHud}, 
	pathToBtnReleased		{_pathToBtnReleased}, 
	pathToBtnPressed		{_pathToBtnPressed}, 
	pathToFont				{_pathToFont},
	hud						{new sf::Texture()},
	currentScale			{1.f,1.f}

{
	hud->loadFromFile(pathToHUD.c_str());
	hudSprite = new sf::Sprite(*hud);

	hudPos.x = static_cast<float>(_wndSize.x) * 0.75f;
	hudPos.y = static_cast<float>(_wndSize.y);

	buttonsPos.x = static_cast<float>(_wndSize.x) / 2.f;
	// Will be use for calculate cur position of each button vertically
	buttonsPos.y = static_cast<float>(_wndSize.y);

	PrepButtons(MODE::MAIN_MENU);
}

void HUD::DrawHUD(sf::RenderWindow& _wnd)
{
	_wnd.draw(*hudSprite);
}

void Hud::HUD::DrawButtons(sf::RenderWindow& _wnd)
{
	std::lock_guard<std::mutex> lk(defMutex);

	for (int i = 0; i < btns.size(); ++i)
	{
		btns[i]->Draw(
			_wnd, 
			sf::Vector2f(
				buttonsPos.x,
				(buttonsPos.y / static_cast<float>(btns.size() + 2)) * static_cast<float>(i + 1))
		);
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

std::optional <Buttons::BtnPurpose> Hud::HUD::CheckButtonsTouch(float _x, float _y)
{
	std::optional <Buttons::BtnPurpose> temp;

	for (int i = 0; i < btns.size(); ++i)
	{
		if (btns[i]->GetTouch(_x, _y))
		{
			temp = btns[i]->GetBtnPurpose();
		}
	}

	return temp;
}

void Hud::HUD::RealeseButtons()
{
	for (auto& el : btns)
	{
		el->SwitchCurrentState(Buttons::BtnState::RELEASED);
	}
}

void Hud::HUD::PrepButtons(MODE _mode, int _lvlCount)
{
	fillBtnsArr(_mode, _lvlCount);
}

void Hud::HUD::fillBtnsArr(MODE _mode, int _lvlCount)
{
	std::lock_guard<std::mutex> lock(defMutex);

	btns.clear();

	switch (_mode)
	{
	case Hud::MODE::MAIN_MENU:
			{
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::START, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Start"));
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::LEADER_BORD, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Leaderbord"));
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Exit"));
			}
			break;

	case Hud::MODE::LVL_SELECT:
			{
				assert(_lvlCount);

				Buttons::BtnPurpose tempB = Buttons::BtnPurpose::LVL_1;
				for (int i = 0; i < _lvlCount; ++i)
				{
					btns.emplace_back(new Buttons::Button(tempB, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
						pathToFont.c_str(),
						(std::string("LVL_") + std::to_string(i + 1)).c_str()
					));
					++tempB;
				}
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Back"));
			}	
			break;

	case Hud::MODE::LEADERS:
			{
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Back"));
			}
			break;

	case Hud::MODE::GAME_PAUSE:
			{
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::CONTINUE, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Continue"));
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Main Menu"));
				btns.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(), "Exit"));
			}	
			break;

	case Hud::MODE::GAME_OVER:
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
		el->Rescale(currentScale);
	}

}


