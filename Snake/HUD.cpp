#include "HUD.h"

using namespace Hud;

HUD::HUD(const char* _pathToHud, const char* _pathToBtnReleased, const char* _pathToBtnPressed, const char* _pathToFont) :
	pathToHUD{_pathToHud}, pathToBtnReleased{_pathToBtnReleased}, pathToBtnPressed{_pathToBtnPressed}, pathToFont{_pathToFont}
{
	hud = new sf::Texture();
	hud->loadFromFile(pathToHUD.c_str());

	hudSprite = new sf::Sprite(*hud);

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
		// Center of the window
		float x = static_cast<float>(_wnd.getSize().x) / 2.f;
		float y = static_cast<float>(_wnd.getSize().y) / static_cast<float>(btns.size() + 2);

		btns[i]->Draw(_wnd, sf::Vector2f(
			x, y * static_cast<float>(i + 1)
		));
	}
}

void Hud::HUD::SetSpriteScale(unsigned int _width, unsigned int _height)
{
	

	if (hud->getSize().x > _width || hud->getSize().y > _height)
	{
		float xFactor = 1.f;
		float yFactor = 1.f;

		if (hud->getSize().x > _width)
		{
			xFactor -= static_cast<float>(hud->getSize().x - _width) / 
				static_cast<float>(hud->getSize().x);
		}
		if (hud->getSize().y > _height)
		{
			yFactor -= static_cast<float>(hud->getSize().y - _height) /
				static_cast<float>(hud->getSize().y);
		}

		std::lock_guard<std::mutex> lk(defMutex);
		hudSprite->setScale(xFactor, yFactor);
		for (auto& el : btns)
		{
			el->Rescale(sf::Vector2f(xFactor, yFactor));
		}
	}

}

std::optional <Buttons::BtnPurpose> Hud::HUD::CheckButtons(float _x, float _y)
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

	case Hud::MODE::GAME_PROCESS:
			{

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
}


