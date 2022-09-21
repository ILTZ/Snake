#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <unordered_map>

#include "BaseD.h"
#include "Mouse.h"
#include "Keyboard.h"


namespace MainWin
{
	enum class Plans
	{
		HUD				= 0,
		FIRST_PLAN		= 1,
		SECOND_PLAN		= 2,

		START = HUD,
		END = SECOND_PLAN,
	};
	Plans operator++(Plans& _x);
	Plans operator--(Plans& _x);

	class MainWindow
	{
	private:
		// Стоило бы отталкиваться от размера спрайтов, я полагаю....
		// ....но чот хз прям.
		const int windowW = 40;
		const int windowH = 30;

		const int wWidth;
		const int wHeight;

	private:
		std::unique_ptr<sf::RenderWindow>	wnd;
		std::unordered_map<Plans, std::shared_ptr<BaseD>>	whatDraw;

	public:
		MainWindow(int _width = 1600, int _height = 1200, const std::string& _title = "DefaultTitle",
			int32_t _style = sf::Style::Titlebar | sf::Style::Close, const sf::ContextSettings& _settings = sf::ContextSettings());

		MainWindow(const MainWindow&) = delete;
		MainWindow& operator=(const MainWindow&) = delete;

	public:
		int Draw();
		bool PollEvents();
		sf::RenderWindow& get();

	public:
		void AddToDrawLayout(const std::shared_ptr<BaseD>& _whatDrow, Plans _plan);

		auto GetKeyboardEvent();
		auto GetMouseEvent();

	private:
		// Draw all of we have in drawLayout
		void drawOther();

	private:
		MS::Mouse mouse;
		KB::Keyboard kb;


	};
}
#endif
