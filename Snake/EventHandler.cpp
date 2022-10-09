#include "EventHandler.h"


EventHandler::EventHandler(
	std::shared_ptr<Hud::HUD> _hud, 
	std::shared_ptr<BaseP::BasePawn> _snakePawn)
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

void EventHandler::HandleKeyEvent(const std::optional<Keyboard::KeyEvent>& _keyEvent, APP_STATE::AppState& _state)
{
	if (!_state.CheckMovebleStates() || !_keyEvent.has_value())
		return;

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
			_state.SetState(APP_STATE::States::GAME_PAUSE);
			hud->PrepButtons(Hud::MODE::GAME_PAUSE);
			break;

		default:
			break;
		}
	}
}

std::optional<EventHandler::HandleResult> EventHandler::HandleMouseEvent(const std::optional<MS::MouseEvent>& _mouseEvent, APP_STATE::AppState& _state)
{
	std::optional<EventHandler::HandleResult> temp;

	if (!_mouseEvent.has_value() || _state.CheckMovebleStates())
		return temp;

	if (_mouseEvent.value().isPressed)
	{
		hud->CheckButtonsTouch(
			static_cast<float>(_mouseEvent.value().wPos.x), 
			static_cast<float>(_mouseEvent.value().wPos.y));
	}
	else
	{
		auto button = hud->CheckButtonsTouch(
			static_cast<float>(_mouseEvent.value().wPos.x), 
			static_cast<float>(_mouseEvent.value().wPos.y));

		hud->RealeseButtons();

		if (button.has_value())
		{
			using namespace APP_STATE;

			temp = EventHandler::HandleResult();

			using bMod = Buttons::BtnPurpose;
			using hMod = Hud::MODE;

			switch (button.value())
			{
			case bMod::START:
				{
					_state.SetState(States::LVL_SELECT);
					//temp.value().gameMode = Hud::MODE::LVL_SELECT;
					SmartPointer::SmartPointer<CLoader::ConfigLoader> loader 
						= new CLoader::ConfigLoader();

					hud->PrepButtons(Hud::MODE::LVL_SELECT, loader->GetLvlCount());
				}
				break;

			case bMod::EXIT:
				_state.ExitApp();
				break;

			case bMod::CONTINUE:
				_state.SetState(States::GAME_PROCESS);
				break;

			case bMod::BACK:
				_state.SetState(States::MAIN_MENU);
				hud->PrepButtons(Hud::MODE::MAIN_MENU);
				break;

			case bMod::LEADER_BORD:
				_state.SetState(States::LEADERS_VIEW);
				hud->PrepButtons(Hud::MODE::LEADERS);
				break;

			case bMod::LVL_1:
				temp.value().gameMode = hMod::LVL_SELECTED;
				temp.value().lvl = CLoader::LVLs::LVL_1;
				break;
			case bMod::LVL_2:
				temp.value().gameMode = hMod::LVL_SELECTED;
				temp.value().lvl = CLoader::LVLs::LVL_2;
				break;
			case bMod::LVL_3:
				temp.value().gameMode = hMod::LVL_SELECTED;
				temp.value().lvl = CLoader::LVLs::LVL_3;
				break;
			case bMod::LVL_4:
				temp.value().gameMode = hMod::LVL_SELECTED;
				temp.value().lvl = CLoader::LVLs::LVL_4;
				break;
			case bMod::LVL_5:
				temp.value().gameMode = hMod::LVL_SELECTED;
				temp.value().lvl = CLoader::LVLs::LVL_5;
				break;

			case bMod::MAIN_MENU:
				_state.SetState(States::MAIN_MENU);
				hud->PrepButtons(Hud::MODE::MAIN_MENU);
				break;

			default:
				break;
			}
		}
	}

	return temp;
	
}


