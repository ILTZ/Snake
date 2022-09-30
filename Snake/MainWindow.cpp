#include "MainWindow.h"

#include <SFML/Window/Event.hpp>

using namespace MainWin;

MainWindow::MainWindow(
	int _width, 
	int _height, 
	const std::string& _title, 
	int32_t _style, 
	const sf::ContextSettings& _settings) :
	wWidth{_width}, 
	wHeight{_height},
	wnd{sf::VideoMode(_width, _height), _title, _style, _settings}
{


}

int MainWindow::DrawLayouts()
{
	if (wnd.isOpen())
	{
		drawOther();
	}
	else
	{
		return 0;
	}

	return 1;
}

void MainWin::MainWindow::DrawHUD()
{
	if (wnd.isOpen() && hud.get())
	{
		hud->DrawHUD(wnd);
	}
}

void MainWin::MainWindow::DrawButtons()
{
	if (wnd.isOpen() && hud.get())
	{
		hud->DrawButtons(wnd);
	}
}

void MainWin::MainWindow::Draw(BaseD& _whatDraw)
{
	_whatDraw.Draw(wnd);
}

bool MainWindow::PollEvents()
{
	sf::Event ev;
	while (wnd.pollEvent(ev))
	{
		// Exit game
		if (ev.type == sf::Event::Closed)
			return false;


		switch (ev.type)
		{
		case sf::Event::MouseButtonPressed:
			mouse.AddPressEvent(ev);
			break;

		case sf::Event::MouseButtonReleased:
			mouse.AddReleaseEvent(ev);
			break;
	
		case sf::Event::KeyPressed:
			kb.AddPressEvent(ev);
			break;

		case sf::Event::KeyReleased:
			kb.AddReleaseEvent(ev);
			break;
		}

	}


	return true;
}

sf::RenderWindow& MainWindow::get()
{
	return wnd;
}

void MainWin::MainWindow::SetHud(std::shared_ptr<Hud::HUD> _hud)
{
	hud = _hud;
}

Hud::HUD& MainWin::MainWindow::GetHUD()
{
	return *hud;
}

void MainWin::MainWindow::AddToDrawLayout(const std::shared_ptr<BaseD>& _whatDrow, Plans _plan)
{
	whatDraw[_plan] = _whatDrow;
}

std::optional<KB::KeyEvent> MainWin::MainWindow::GetKeyboardEvent()
{
	return kb.GetEvent();
}

std::optional<MS::MouseEvent> MainWin::MainWindow::GetMouseEvent()
{
	return mouse.GetEvent();
}

void MainWin::MainWindow::drawOther()
{
	for (auto i = Plans::END; i >= Plans::START; --i)
	{
		if (whatDraw[i].get())
			whatDraw[i]->Draw(wnd);
	}
}

Plans MainWin::operator++(Plans& _x)
{
	return _x = static_cast<Plans>(std::underlying_type<Plans>::type(_x) + 1);
}

Plans MainWin::operator--(Plans& _x)
{
	return _x = static_cast<Plans>(std::underlying_type<Plans>::type(_x) - 1);
}
