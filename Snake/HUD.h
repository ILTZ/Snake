#ifndef HUD_H
#define HUD_H

#include <vector>
#include <vector>
#include <string>
#include <optional>
#include <mutex>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Button.h"
#include "Widget.h"

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
		struct WidgetsProperties
		{
			std::unique_ptr<BaseWidget> widget;

			std::string vectorText;
			const sf::Vector2f widgetPos;
		};

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
		// Its position will always be in the last quarter of the screen
		sf::Vector2f hudPos;
		// Its position will always be in the midle of the screen
		sf::Vector2f buttonsPos;
		// Need for recreated buttons
		sf::Vector2f currentScale;

	private:

	private:
		std::vector <SmartPointer::SmartPointer<Buttons::Button>> btns;

	private:
		const unsigned int baseWidgetArraySize = 4;
		std::vector<std::shared_ptr<BaseWidget>> widgetArr;

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
		void SetScale		(const sf::Vector2f& _newScale);
		
	public:
		const sf::Vector2u GetHUDSize()			const;
		const sf::Vector2f GetHudPosition()		const;
		void SetHudPosition(const sf::Vector2f& _newPos);

	public:
		const sf::Vector2f GetButtonsPosition()					const;
		void SetButtonsPosition(const sf::Vector2f& _newPos);
		void PrepButtons(MODE _mode, int _lvlCount = 0);

		void RealeseButtons();
		std::optional <Buttons::BtnPurpose>	CheckButtonsTouch(
			float _x,
			float _y);

	public:
		void AddWidget(std::shared_ptr<BaseWidget> _widget);

	private:
		void fillBtnsArr(MODE _mode, int _lvlCount = 0);
		void drawWidgets(sf::RenderWindow& _wnd);
	};
}

#endif

