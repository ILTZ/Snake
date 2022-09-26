#include "EventHandler.h"

EventHandler::EventHandler(std::shared_ptr<Hud::HUD> _hud, std::shared_ptr<BaseP::BasePawn> _snakePawn)
	: hud{_hud}, pawn{_snakePawn}
{

}

void EventHandler::SetPawn(std::shared_ptr<BaseP::BasePawn> _pawn)
{
	pawn = _pawn;
}

void EventHandler::SetHud(std::shared_ptr<Hud::HUD> _hud)
{
	hud = _hud;
}

std::optional<Hud::MODE> EventHandler::HandleKeyEvent(const std::optional<KB::KeyEvent>& _keyEvent, Hud::MODE _mode)
{
	std::optional<Hud::MODE> temp;

	if ((_mode != Hud::MODE::GAME_PROCESS) || !_keyEvent.has_value())
		return temp;

	if (!_keyEvent.value().isPressed)
	{
		switch (_keyEvent.value().key)
		{
		case sf::Keyboard::Key::W:
		case sf::Keyboard::Key::Up:
			pawn->SetDir(BaseP::Direction::TOP);
			break;

		case sf::Keyboard::Key::S:
		case sf::Keyboard::Key::Down:
			pawn->SetDir(BaseP::Direction::DOWN);
			break;

		case sf::Keyboard::Key::A:
		case sf::Keyboard::Key::Left:
			pawn->SetDir(BaseP::Direction::LEFT);
			break;

		case sf::Keyboard::Key::D:
		case sf::Keyboard::Key::Right:
			pawn->SetDir(BaseP::Direction::RIGHT);
			break;

		case sf::Keyboard::Key::Escape:
		case sf::Keyboard::Key::P:
			temp = Hud::MODE::GAME_PAUSE;
			break;

		default:
			break;
		}
	}
	return temp;
}

std::optional<Hud::MODE> EventHandler::HandleMouseEvent(const std::optional<MS::MouseEvent>& _mouseEvent, Hud::MODE _mode)
{
	std::optional<Hud::MODE> temp;

	if (!_mouseEvent.has_value() || _mode == Hud::MODE::GAME_PROCESS)
		return temp;

	if (_mouseEvent.value().isPressed)
	{
		hud->CheckButtons(static_cast<float>(_mouseEvent.value().wPos.x), 
			static_cast<float>(_mouseEvent.value().wPos.y));
	}
	else
	{
		auto button = hud->CheckButtons(static_cast<float>(_mouseEvent.value().wPos.x), 
			static_cast<float>(_mouseEvent.value().wPos.y));
		hud->RealeseButtons();

		if (button.has_value())
		{
			using bMod = Buttons::Btn;
			using hMod = Hud::MODE;

			switch (button.value().first)
			{
			case bMod::START:
				temp = Hud::MODE::LVL_CHOISE;
				break;

			case bMod::EXIT:
				temp = hMod::EXIT;
				break;

			case bMod::CONTINUE:
				temp = hMod::GAME_PROCESS;
				break;

			case bMod::BACK:
				temp = hMod::MAIN_MENU;

			case bMod::LEADER_BORD:
				temp = hMod::LEADERS;
				break;

			case bMod::LVL:

				break;

			case bMod::MAIN_MENU:
				temp = hMod::MAIN_MENU;
				break;

			default:
				break;
			}
		}
	}

	return temp;
	
}


