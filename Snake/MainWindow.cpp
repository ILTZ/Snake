#include "MainWindow.h"

#include <SFML/Window/Event.hpp>

MainWindow::MainWindow(int _width, int _height, const std::string& _title, int32_t _style, const sf::ContextSettings& _settings)
{
	wnd = std::make_unique<sf::RenderWindow>
		(sf::VideoMode(_width, _height), _title, _style, _settings);

}

int MainWindow::Draw()
{
	if (wnd->isOpen())
	{






		wnd->clear();

		wnd->display();
	}
	else
	{
		return 0;
	}


	return 1;
}

bool MainWindow::PollEvents()
{
	sf::Event ev;
	while (wnd.get()->pollEvent(ev))
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
	return *wnd.get();
}
