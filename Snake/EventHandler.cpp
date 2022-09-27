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
			hud->prepButtons(Hud::MODE::GAME_PAUSE);
			break;

		default:
			break;
		}
	}
	return temp;
}

std::optional<EventHandler::HandleResult> EventHandler::HandleMouseEvent(const std::optional<MS::MouseEvent>& _mouseEvent, Hud::MODE _mode)
{
	std::optional<EventHandler::HandleResult> temp;

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
			temp = EventHandler::HandleResult();

			using bMod = Buttons::Btn;
			using hMod = Hud::MODE;

			switch (button.value())
			{
			case bMod::START:
				{
					temp.value().gameMode = Hud::MODE::LVL_SELECT;
					SmartPointer::SmartPointer<CLoader::ConfigLoader> loader 
						= new CLoader::ConfigLoader();

					hud->prepButtons(Hud::MODE::LVL_SELECT, loader->GetLvlCount());
				}
				break;

			case bMod::EXIT:
				temp.value().gameMode = hMod::EXIT;
				break;

			case bMod::CONTINUE:
				temp.value().gameMode = hMod::GAME_PROCESS;
				break;

			case bMod::BACK:
				temp.value().gameMode = hMod::MAIN_MENU;
				hud->prepButtons(Hud::MODE::MAIN_MENU);
				break;

			case bMod::LEADER_BORD:
				temp.value().gameMode = hMod::LEADERS;
				hud->prepButtons(Hud::MODE::LEADERS);
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
				temp.value().gameMode = hMod::MAIN_MENU;
				hud->prepButtons(Hud::MODE::MAIN_MENU);

				break;

			default:
				break;
			}
		}
	}

	return temp;
	
}


