#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Mouse.h"
#include "Keyboard.h"
#include "HUD.h"
#include "BaseDrawable.h"
#include "ConfigLoader.h"

namespace MainWin
{
	class MainWindow
	{
	private:
		unsigned int	wWidth;
		unsigned int	wHeight;
	
		std::string		pathToFont  = "";

	private:
		const float hudPart			= 0.25f;
		const float gameFieldPart	= 0.75f;

	private:
		struct Background
		{
			Background(
				const std::string& _pathToTexture, 
				unsigned int _width, 
				unsigned int _height);

			sf::Texture bText;
			sf::Sprite	bSprite;

			void Draw(sf::RenderWindow& _wnd);
		};
		SmartPointer::SmartPointer<Background> background;
		
	private:
		sf::RenderWindow			wnd;
		std::shared_ptr<UI::Ui>		hud;

	public:
		MainWindow(
			CLoader::Loader* _loder,
			const std::string& _title = "DefaultTitle",
			int32_t _style = sf::Style::Titlebar | sf::Style::Close,
			const sf::ContextSettings& _settings = sf::ContextSettings());

		MainWindow				(const MainWindow&) = delete;
		MainWindow& operator=	(const MainWindow&) = delete;

	public: //wnd funcs
		void Draw(BaseDrawable& _whatDraw);
		void DrawUI(const APP_STATE::AppState &_curState);
		void DrawLoadingScreen();

	public:
		bool				PollEvents();
		sf::RenderWindow&	get();

	public: //hud funcs
		void		SetHud(std::shared_ptr<UI::Ui> _hud);
		UI::Ui&		GetUI();

	public:
		const sf::Vector2u GetHudTargetSize()		const;
		const sf::Vector2u GetGameFieldTargetSize() const;

	public:
		std::optional<Keyboard::KeyEvent>		GetKeyboardEvent();
		std::optional<Keyboard::TextEvent>		GetTextEvent();
		std::optional<MS::MouseEvent>			GetMouseEvent();


	private:
		MS::Mouse			mouse;
		Keyboard::Keyboard	kb;

	};
}
#endif
