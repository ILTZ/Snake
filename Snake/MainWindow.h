#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <unordered_map>

#include "Mouse.h"
#include "Keyboard.h"
#include "HUD.h"
#include "BaseDrawable.h"

namespace MainWin
{
	class MainWindow
	{
	private:
		const unsigned int wWidth;
		const unsigned int wHeight;
	
	private:
		const float hudPart			= 0.25f;
		const float gameFieldPart	= 0.75f;

	private:
		sf::RenderWindow			wnd;
		std::shared_ptr<Hud::HUD>	hud;

	public:
		MainWindow(
			unsigned int _width = 1600u, 
			unsigned int _height = 1200u, 
			const std::string& _title = "DefaultTitle",
			int32_t _style = sf::Style::Titlebar | sf::Style::Close, 
			const sf::ContextSettings& _settings = sf::ContextSettings());

		MainWindow				(const MainWindow&) = delete;
		MainWindow& operator=	(const MainWindow&) = delete;

	public: //wnd funcs
		void				Draw(BaseDrawable& _whatDraw);

		bool				PollEvents();
		sf::RenderWindow&	get();

	public: //hud funcs
		void		SetHud(std::shared_ptr<Hud::HUD> _hud);
		Hud::HUD&	GetHUD();
		void		DrawHUD();
		void		DrawButtons();

	public:
		const sf::Vector2u GetHudTargetSize()		const;
		const sf::Vector2u GetGameFieldTargetSize() const;

	public:
		std::optional<Keyboard::KeyEvent>		GetKeyboardEvent();
		std::optional<Keyboard::TextEvent>		GetTextEvent();
		std::optional<MS::MouseEvent>			GetMouseEvent();


	private:
		MS::Mouse mouse;
		Keyboard::Keyboard kb;

	};
}
#endif
