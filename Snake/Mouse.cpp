#include "Mouse.h"

#ifndef NDEBUG
#define LOG(str) printf("%s", str) 
#endif

using namespace MS;

MouseEvent::MouseEvent(const sf::Event& _ev, bool _isPressed) : button{ _ev.mouseButton.button },
isPressed{ _isPressed }, wPos{ _ev.mouseButton.x, _ev.mouseButton.y }
{

}

Mouse::Mouse()
{

}

void Mouse::AddPressEvent(const sf::Event& _ev)
{
	eventsQ.push(MouseEvent(_ev, true));

#ifndef NDEBUG
	LOG("Add_mouse_press_event\n");
#endif
}

void Mouse::AddReleaseEvent(const sf::Event& _ev)
{
	eventsQ.push(MouseEvent(_ev, false));

#ifndef NDEBUG
	LOG("Add_mouse_release_event\n");
#endif
}




