#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Window/Keyboard.hpp>
#include "ControlBase.h"

// Include keyboard class 
namespace Keyboard
{
	struct KeyEvent
	{
		KeyEvent(const sf::Event& _ev, bool _isPressed);

		sf::Keyboard::Key key;
		bool isPressed;
	};

	struct TextEvent
	{
		TextEvent(const sf::Event& _ev);

		char symbol;
		bool shiftPressed;

		const char GetChar() const;
	};

	class Keyboard : public ControlBase::ControlBase<KeyEvent>
	{
	private:
		std::queue<TextEvent> textQ;

	public:
		Keyboard() = default;

	public:
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;

	public:
		void AddPressEvent(const sf::Event& _ev)	override;
		void AddReleaseEvent(const sf::Event& _ev)	override;
		
		void AddCharEvent(const sf::Event& _ev);
		std::optional<TextEvent> GetCharEvent();

	private:
		void flushTextQ();
	};
}

#endif

