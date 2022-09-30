#ifndef HUD_H
#define HUD_H

#include <vector>
#include <string>
#include <optional>
#include <mutex>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Button.h"


namespace Hud
{
	enum class MODE
	{
		MAIN_MENU		= 0,
		LVL_SELECT		= 1,
		LVL_SELECTED	= 2,
		GAME_PROCESS	= 3,
		GAME_PAUSE		= 4,
		GAME_OVER		= 5,
		LEADERS			= 6,
		EXIT			= 7,

	};

	class HUD
	{
	private:
		const std::string pathToHUD;
		const std::string pathToBtnReleased;
		const std::string pathToBtnPressed;
		const std::string pathToFont;

	private:
		std::mutex defMutex;

	private:
		SmartPointer::SmartPointer<sf::Texture> hud;
		SmartPointer::SmartPointer<sf::Sprite>	hudSprite;

	private:
		std::vector <SmartPointer::SmartPointer<Buttons::Button>> btns;

	public:
		HUD(
			const char* _pathToHud, 
			const char* _pathToBtnReleased, 
			const char* _pathToBtnPressed, 
			const char* _pathToFont);

	public:
		HUD(const HUD&)				= delete;
		HUD& operator=(const HUD&)	= delete;

	public:
		void DrawHUD		(sf::RenderWindow& _wnd);
		void DrawButtons	(sf::RenderWindow& _wnd);
		void SetSpriteScale	(unsigned int _width, unsigned int _height);

	public:
		std::optional <Buttons::Btn>	CheckButtons(float _x, float _y);
		void							RealeseButtons();

	public:
		void PrepButtons(MODE _mode, int _lvlCount = 0);

	private:
		void fillBtnsArr(MODE _mode, int _lvlCount = 0);

	};
}

#endif

