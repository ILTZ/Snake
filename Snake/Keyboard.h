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

	class Keyboard : public ControlBase::ControlBase<KeyEvent>
	{
	public:
		Keyboard() = default;

	public:
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;

	public:
		void AddPressEvent(const sf::Event& _ev)	override;
		void AddReleaseEvent(const sf::Event& _ev)	override;


	private:

	};
}

#endif

