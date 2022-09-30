#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <unordered_map>

#include "Mouse.h"
#include "Keyboard.h"
#include "HUD.h"
#include "BaseD.h"

namespace MainWin
{
	class MainWindow
	{
	private:
		const int wWidth;
		const int wHeight;

	private:
		sf::RenderWindow									wnd;
		std::shared_ptr<Hud::HUD>							hud;

	public:
		MainWindow(
			int _width = 1600, 
			int _height = 1200, 
			const std::string& _title = "DefaultTitle",
			int32_t _style = sf::Style::Titlebar | sf::Style::Close, 
			const sf::ContextSettings& _settings = sf::ContextSettings());

		MainWindow				(const MainWindow&) = delete;
		MainWindow& operator=	(const MainWindow&) = delete;

	public: //wnd funcs
		void				Draw(BaseD& _whatDraw);
		bool				PollEvents();
		sf::RenderWindow&	get();

	public: //hud funcs
		void		SetHud(std::shared_ptr<Hud::HUD> _hud);
		Hud::HUD&	GetHUD();
		void		DrawHUD();
		void		DrawButtons();

	public:
		std::optional<KB::KeyEvent>		GetKeyboardEvent();
		std::optional<MS::MouseEvent>	GetMouseEvent();

	private:
		MS::Mouse mouse;
		KB::Keyboard kb;

	};
}
#endif
