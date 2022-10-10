#include "MainWindow.h"
#include "ConfigLoader.h"

#include <SFML/Window/Event.hpp>
#include <cassert>

using namespace MainWin;

MainWindow::MainWindow(
	unsigned int _width, 
	unsigned int _height, 
	const std::string& _title, 
	int32_t _style, 
	const sf::ContextSettings& _settings) :
	wWidth{_width}, 
	wHeight{_height},
	wnd{sf::VideoMode(_width, _height), _title, _style, _settings}
{


}

void MainWin::MainWindow::DrawHUD()
{
	assert(hud.get());

	if (wnd.isOpen())
		hud->DrawHUD(wnd);	
}

void MainWin::MainWindow::DrawButtons()
{
	assert(hud.get());

	if (wnd.isOpen())
		hud->DrawButtons(wnd);	
}

const sf::Vector2u MainWin::MainWindow::GetHudTargetSize() const
{
	return sf::Vector2u(
		static_cast<unsigned int>(static_cast<float>(wWidth) * hudPart),
		wHeight
	);
}

const sf::Vector2u MainWin::MainWindow::GetGameFieldTargetSize() const
{
	return sf::Vector2u(
		static_cast<unsigned int>(static_cast<float>(wWidth) * gameFieldPart),
		wHeight
	);
}

void MainWin::MainWindow::Draw(BaseD& _whatDraw)
{
	_whatDraw.Draw(wnd);
}

void MainWin::MainWindow::Draw(BaseDrawable& _whatDraw)
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
	// Last quarter of the window
	hud->SetHudPosition(sf::Vector2f(
		static_cast<float>(wnd.getSize().x) * (1.f - hudPart), 0.f));
	// Midle of the window
	hud->SetButtonsPosition(sf::Vector2f(
		static_cast<float>(wnd.getSize().x) / 2.f,
		static_cast<float>(wnd.getSize().y)));
}

Hud::HUD& MainWin::MainWindow::GetHUD()
{
	return *hud;
}

std::optional<Keyboard::KeyEvent> MainWin::MainWindow::GetKeyboardEvent()
{
	return kb.GetEvent();
}

std::optional<MS::MouseEvent> MainWin::MainWindow::GetMouseEvent()
{
	return mouse.GetEvent();
}


