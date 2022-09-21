#include "HUD.h"

using namespace Hud;

HUD::HUD(const char* _pathToHud, const char* _pathToBtnReleased, const char* _pathToBtnPressed, const char* _pathToFont) :
	pathToHUD{_pathToHud}, pathToBtnReleased{_pathToBtnReleased}, pathToBtnPressed{_pathToBtnPressed}, pathToFont{_pathToFont}
{
	hud = new sf::Texture();
	hud->loadFromFile(pathToHUD.c_str());

	hudSprite = new sf::Sprite(*hud);

	prepButtons(MODE::MAIN_MENU);
}

void HUD::Draw(sf::RenderWindow& _wnd)
{
	for (int i = 0; i < btns.size(); ++i)
	{
		// Center of the window
		float x = static_cast<float>(_wnd.getSize().x) / 2.f;
		float y = static_cast<float>(_wnd.getSize().y) / static_cast<float>(btns.size() + 2);

		btns[i]->Draw(_wnd, sf::Vector2f(
			x, y * static_cast<float>(i + 1)
		));		
	}

	_wnd.draw(*hudSprite);
}

void Hud::HUD::SetSpriteScale(unsigned int _width, unsigned int _height, unsigned int _lwlW, unsigned int _lwlH)
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

		hudSprite->setScale(xFactor, yFactor);
		for (auto& el : btns)
		{
			el->Rescale(sf::Vector2f(xFactor, yFactor));
		}
	}

}

std::optional <std::pair<Buttons::Btn, Buttons::BtnMode>> Hud::HUD::CheckButtons(float _x, float _y)
{
	std::optional <std::pair<Buttons::Btn, Buttons::BtnMode>> temp;

	for (int i = 0; i < btns.size(); ++i)
	{
		if (btns[i]->GetTouch(_x, _y);)
		{
			temp = std::make_pair(btns[i]->GetBtnDest(), btns[i]->GetBtnMode());
		}
	}

	return temp;
}

void Hud::HUD::RealeseButtons()
{
	for (auto& el : btns)
	{
		el->SwitchCurrentState(Buttons::BtnMode::RELEASED);
	}
}

void Hud::HUD::prepButtons(MODE _mode, int _lvlCount)
{
	fillBtnsArr(_mode, _lvlCount);
}


void Hud::HUD::fillBtnsArr(MODE _mode, int _lvlCount)
{
	btns.clear();

	switch (_mode)
	{
	case Hud::MODE::MAIN_MENU:
		btns.emplace_back(new Buttons::Button(Buttons::Btn::START, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Start"));
		btns.emplace_back(new Buttons::Button(Buttons::Btn::LEADER_BORD, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Leaderbord"));
		btns.emplace_back(new Buttons::Button(Buttons::Btn::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Exit"));
		break;

	case Hud::MODE::LVL_CHOISE:
		for (int i = 0; i < _lvlCount; ++i)
		{
			btns.emplace_back(new Buttons::Button(Buttons::Btn::LVL, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(),
				(std::string("LVL_") + std::to_string(i + 1)).c_str()
				));
		}
		break;

	case Hud::MODE::GAME_PROCESS:
		
		break;

	case Hud::MODE::GAME_PAUSE:
		btns.emplace_back(new Buttons::Button(Buttons::Btn::CONTINUE, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Continue"));
		btns.emplace_back(new Buttons::Button(Buttons::Btn::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Main Menu"));
		btns.emplace_back(new Buttons::Button(Buttons::Btn::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Exit"));
		break;

	case Hud::MODE::GAME_OVER:
		btns.emplace_back(new Buttons::Button(Buttons::Btn::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Main Menu"));
		btns.emplace_back(new Buttons::Button(Buttons::Btn::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
			pathToFont.c_str(), "Exit"));
		break;

	default:
		break;
	}
}


