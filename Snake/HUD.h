#ifndef HUD_H
#define HUD_H

#include <vector>
#include <string>
#include <optional>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Button.h"
#include "BaseD.h"

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

	class HUD : public BaseD
	{
	private:
		const std::string pathToHUD;
		const std::string pathToBtnReleased;
		const std::string pathToBtnPressed;
		const std::string pathToFont;

	private:
		SmartPointer::SmartPointer<sf::Texture> hud;
		SmartPointer::SmartPointer<sf::Sprite> hudSprite;

	private:
		std::vector <SmartPointer::SmartPointer<Buttons::Button>> btns;

	public:
		HUD(const char* _pathToHud, const char* _pathToBtnReleased, const char* _pathToBtnPressed, const char* _pathToFont);

	public:
		HUD(const HUD&) = delete;
		HUD& operator=(const HUD&) = delete;

	public:
		void Draw(sf::RenderWindow& _wnd) override;
		void SetSpriteScale(unsigned int _width, unsigned int _height,
			unsigned int _lwlW, unsigned int _lwlH);

	public:
		std::optional <std::pair<Buttons::Btn, Buttons::BtnMode>> CheckButtons(float _x, float _y);
		void RealeseButtons();

	public:
		void prepButtons(MODE _mode, int _lvlCount = 0);

	private:
		void fillBtnsArr(MODE _mode, int _lvlCount = 0);

	};
}

#endif

