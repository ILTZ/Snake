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

void EventHandler::HandleKeyEvent(
	const std::optional<Keyboard::KeyEvent>& _keyEvent, 
	APP_STATE::AppState& _state)
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
			hud->PrepButtons(_state.GetState());
			break;
		
		default:
			break;
		}

		
	}
}

void EventHandler::HandleCharEvent(
	const std::optional<Keyboard::TextEvent>& _keyEvent,
	APP_STATE::AppState& _state)
{
	if (!_keyEvent.has_value())
		return;

	if (_state.GetState() == APP_STATE::States::INPUT_NAME)
	{
		if (hud->GetInputNameWidget().has_value())
		{
			hud->GetInputNameWidget().value()->AddSymbol(_keyEvent.value().GetChar());
		}
	}
}


std::optional<CLoader::LVLs> EventHandler::HandleMouseEvent(
	const std::optional<MS::MouseEvent>& _mouseEvent, 
	APP_STATE::AppState& _state)
{
	if (!_mouseEvent.has_value() || _state.CheckMovebleStates())
		return {};

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
			using bMod = Buttons::BtnPurpose;

			switch (button.value())
			{
			case bMod::START:
				{
					_state.SetState(States::LVL_SELECT);
					SmartPointer::SmartPointer<CLoader::ConfigLoader> loader 
						= new CLoader::ConfigLoader();

					hud->PrepButtons(States::LVL_SELECT, loader->GetLvlCount());
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
				hud->PrepButtons(_state.GetState());
				break;

			case bMod::LEADER_BORD:
				_state.SetState(States::LEADERS_VIEW);
				hud->PrepButtons(_state.GetState());
				break;
			
			case bMod::NAME_ACEPT:
				_state.SetState(States::GAME_OVER);
				hud->PrepButtons(_state.GetState());
				break;

			// Lvl selected {
			case bMod::LVL_1:
				_state.SetState(States::LVL_SELECTED);
				return CLoader::LVLs::LVL_1;
				
			case bMod::LVL_2:
				_state.SetState(States::LVL_SELECTED);
				return CLoader::LVLs::LVL_2;
				
			case bMod::LVL_3:
				_state.SetState(States::LVL_SELECTED);
				return CLoader::LVLs::LVL_3;
				
			case bMod::LVL_4:
				_state.SetState(States::LVL_SELECTED);
				return CLoader::LVLs::LVL_4;
				
			case bMod::LVL_5:
				_state.SetState(States::LVL_SELECTED);
				return CLoader::LVLs::LVL_5;	// Lvl selected }
					

			case bMod::MAIN_MENU:
				_state.SetState(States::MAIN_MENU);
				hud->PrepButtons(_state.GetState());
				break;

			default:
				break;
			}
		}
	}

	return {};
}


