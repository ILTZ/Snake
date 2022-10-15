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
#include "InfoWidget.h"
#include "AppState.h"
//#include "BaseDrawable.h"
#include "Layout.h"
#include "ConfigLoader.h"

namespace Hud
{
	
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
		// Its position will always be in the midle of the screen
		sf::Vector2f buttonsPos;
		// Need for recreated buttons
		sf::Vector2f currentScale;

	private:

	private:
		std::vector <std::shared_ptr<Buttons::Button>>	btnsLogicArr;
		SmartPointer::SmartPointer<LAYOUT::Layout>		btnsLayout;
		SmartPointer::SmartPointer<LAYOUT::Layout>		widgetLayout;

	private:
		const unsigned int baseWidgetArraySize = 3;
		std::vector<std::shared_ptr<BaseDrawable>> widgetArr;

	public:
		HUD(CLoader::HudConfigs& _configs);

	public:
		HUD(const HUD&)				= delete;
		HUD& operator=(const HUD&)	= delete;

	public:
		void DrawHUD		(sf::RenderWindow& _wnd);
		void DrawButtons	(sf::RenderWindow& _wnd);
		void SetScale		(const sf::Vector2f& _newScale);
		
	public:
		const sf::Vector2u GetHUDSize()					const;
		const sf::Vector2f GetHudSpritePosition()		const;
		void SetHudSpritePosition(const sf::Vector2f& _newPos);

	public:
		const sf::Vector2f GetButtonsPosition()					const;
		void SetButtonsPosition(const sf::Vector2f& _newPos);
		void PrepButtons(APP_STATE::States _state, int _lvlCount = 0);

		void RealeseButtons();
		std::optional <Buttons::BtnPurpose>	CheckButtonsTouch(
			float _x,
			float _y);

	public:
		void AddWidget(std::shared_ptr<BaseDrawable> _widget);
		void ClearWidgets();

	private:
		void drawWidgets(sf::RenderWindow& _wnd);
	};
}

#endif

