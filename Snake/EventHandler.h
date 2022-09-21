#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Keyboard.h"
#include "Mouse.h"

#include "HUD.h"
#include "SnakeBody.h"

class EventHandler
{
private:
	std::shared_ptr<Hud::HUD>			hud;
	std::shared_ptr<Snake::SnakeBody>	snakeBody;


public:
	EventHandler(auto _hud, auto _snakePawn);

public:
	EventHandler(const EventHandler&) = delete;
	EventHandler& operator=(const EventHandler&) = delete;

public:
	void HandleKeyEvent(const KB::KeyEvent& _keyEvent, Hud::MODE _mode);
	void HandleMouseEvent(const MS::MouseEvent& _mouseEvent, Hud::MODE _mode);

private:

};

#endif
