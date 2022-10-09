#include "Keyboard.h"

Keyboard::KeyEvent::KeyEvent(const sf::Event& _ev, bool _isPressed) :
	key{ _ev.key.code }, isPressed{ _isPressed }
{

}

void Keyboard::Keyboard::AddPressEvent(const sf::Event& _ev)
{
	eventsQ.push(KeyEvent(_ev, true));
	trimBuffer(eventsQ);
}

void Keyboard::Keyboard::AddReleaseEvent(const sf::Event& _ev)
{
	eventsQ.push(KeyEvent(_ev, false));
	trimBuffer(eventsQ);
}

void Keyboard::Keyboard::AddCharEvent(const sf::Event& _ev)
{
	textQ.push(_ev);
}

std::optional<Keyboard::TextEvent> Keyboard::Keyboard::GetCharEvent()
{
	if (textQ.size() > 0)
	{
		TextEvent temp = textQ.front();
		textQ.pop();

		return temp;
	}

	return {};
}

void Keyboard::Keyboard::flushTextQ()
{
	textQ = std::queue<TextEvent>();
}

Keyboard::TextEvent::TextEvent(const sf::Event& _ev) : 
	symbol{0}, shiftPressed{false}
{
	if (_ev.text.unicode < 128)
	{
		symbol = static_cast<char>(_ev.text.unicode);
		shiftPressed = _ev.key.shift;
	}
}

char Keyboard::TextEvent::GetChar()
{
	if (shiftPressed)
		return std::toupper(symbol);

	return symbol;
}
