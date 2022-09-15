#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "Mouse.h"
#include "Keyboard.h"

class MainWindow
{
private:
	std::unique_ptr<sf::RenderWindow> wnd;


public:
	MainWindow(int _width = 800, int _height = 600, const std::string& _title = "DefaultTitle", 
		int32_t _style = sf::Style::Default, const sf::ContextSettings& _settings = sf::ContextSettings());

	MainWindow(const MainWindow&)				= delete;
	MainWindow& operator=(const MainWindow&)	= delete;

public:
	int Draw();
	bool PollEvents();

private:
	MS::Mouse mouse;
	KB::Keyboard kb;

};

#endif
