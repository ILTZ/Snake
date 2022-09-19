#include "HUD.h"

using namespace Hud;

HUD::HUD(const char* _pathToHud, const char* _pathToBtnS, const char* _pathToBtnU, const char* _pathToFont) :
	pathToHUD{_pathToHud}, pathToBtnStay{_pathToBtnS}, pathToBtnUp{_pathToBtnU}, pathToFont{_pathToFont}
{
	hud = new sf::Texture();
	hud->loadFromFile(pathToHUD.c_str());


}

void HUD::Draw(sf::RenderWindow& _wnd, MODE _mode)
{

}

void Hud::HUD::prepBtnsArr(MODE _mode)
{
	switch (_mode)
	{
	case Hud::MODE::MAIN_MENU:

		break;

	case Hud::MODE::GAME_PROCESS:
		break;
	case Hud::MODE::GAME_PAUSE:
		break;
	case Hud::MODE::GAME_OVER:
		break;
	default:
		break;
	}
}


