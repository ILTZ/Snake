#ifndef HUD_H
#define HUD_H

#include <vector>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Button.h"

namespace Hud
{
	enum class MODE
	{
		MAIN_MENU		= 0,
		LVL_CHOISE		= 1,
		GAME_PROCESS	= 2,
		GAME_PAUSE		= 3,
		GAME_OVER		= 4,
	};

	class HUD
	{
	private:
		const std::string pathToHUD;
		const std::string pathToBtnStay;
		const std::string pathToBtnUp;
		const std::string pathToFont;

	private:
		SmartPointer::SmartPointer<sf::Texture> hud;
		std::vector <SmartPointer::SmartPointer<Buttons::Button>> btns;

	public:
		HUD(const char* _pathToHud, const char* _pathToBtnS, const char* _pathToBtnU, const char* _pathToFont);

	public:
		HUD(const HUD&) = delete;
		HUD& operator=(const HUD&) = delete;

	public:
		void Draw(sf::RenderWindow& _wnd, MODE _mode);

	public:



	private:
		void prepBtnsArr(MODE _mode);

	};
}

#endif

