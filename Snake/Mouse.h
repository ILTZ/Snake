#ifndef MOUSE_H
#define MOUSE_H

#include <SFML/Window/Mouse.hpp>
#include "ControlBase.h"

// Include mouse event func
namespace MS
{
	struct MouseEvent
	{
		MouseEvent(const sf::Event& _ev, bool _isPressed);

		sf::Mouse::Button button;
		bool isPressed;

		sf::Vector2i fPos;
		sf::Vector2i wPos;
	};

	class Mouse : public ControlBase::ControlBase<MouseEvent>
	{
	private:
		std::unique_ptr<sf::Mouse>			mouse;

	public:
		Mouse();

	public:
		Mouse(const Mouse&)							= delete;
		Mouse& operator=(const Mouse&)				= delete;

	public:
		void AddPressEvent(const sf::Event& _ev)	override;
		void AddReleaseEvent(const sf::Event& _ev)	override;

	};
}

#endif

