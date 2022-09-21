#include "EventHandler.h"

EventHandler::EventHandler(auto _hud, auto _snakePawn) : hud{_hud}, snakeBody{_snakePawn}
{

}

void EventHandler::HandleKeyEvent(const KB::KeyEvent& _keyEvent, Hud::MODE _mode)
{
	if ((_mode != Hud::MODE::GAME_PROCESS) && (!_keyEvent.isPressed))
		return;

	switch (_keyEvent.key)
	{
	case sf::Keyboard::Key::W:
	case sf::Keyboard::Key::Up:
		snakeBody->SetDir(Snake::Direction::TOP);
		break;

	case sf::Keyboard::Key::S:
	case sf::Keyboard::Key::Down:
		snakeBody->SetDir(Snake::Direction::DOWN);
		break;

	case sf::Keyboard::Key::A:
	case sf::Keyboard::Key::Left:
		snakeBody->SetDir(Snake::Direction::LEFT);
		break;

	case sf::Keyboard::Key::D:
	case sf::Keyboard::Key::Right:
		snakeBody->SetDir(Snake::Direction::RIGHT);
		break;

	case sf::Keyboard::Key::Escape:
	case sf::Keyboard::Key::P:

		break;

	default:
		break;
	}
}

void EventHandler::HandleMouseEvent(const MS::MouseEvent& _mouseEvent, Hud::MODE _mode)
{
	if (_mode == Hud::MODE::GAME_PROCESS)
		return;

	if (_mouseEvent.isPressed)
	{
		auto button = hud->CheckButtons(_mouseEvent.wPos.x, _mouseEvent.wPos.y);
	}
	else
	{
		
	}

	
	
}


