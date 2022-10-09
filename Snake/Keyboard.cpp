#include "Keyboard.h"

#ifndef NDEBUG
#define LOG(str) printf("%s", str) 
#endif

Keyboard::KeyEvent::KeyEvent(const sf::Event& _ev, bool _isPressed) :
	key{ _ev.key.code }, isPressed{ _isPressed }
{

}

void Keyboard::Keyboard::AddPressEvent(const sf::Event& _ev)
{
	eventsQ.push(KeyEvent(_ev, true));

#ifndef NDEBUG
	LOG("Add_keyboard_press_event\n");
#endif
}

void Keyboard::Keyboard::AddReleaseEvent(const sf::Event& _ev)
{
	eventsQ.push(KeyEvent(_ev, false));

#ifndef NDEBUG
	LOG("Add_keyboard_release_event\n");
#endif
}
