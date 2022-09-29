#include "GameSession.h"

GameSession::GameSession(MainWin::MainWindow* _wnd, 
	std::shared_ptr<Snake::SnakeBody> _pawn,
	std::shared_ptr<GraphicField::GraphicField> _gp,
	std::shared_ptr<Logic::LogicField> _lField) : 
	wnd{_wnd}, snake{_pawn}, gp{_gp}, logicField{_lField},
	stepTime{10.f}, curPoints{0}, speedMyltiply{1.f}
{

}

GameSession::~GameSession()
{
	snake.reset();
	gp.reset();
}

Hud::MODE GameSession::GameFrame(Hud::MODE _curMode)
{
	// if player press <exit> key 
	if (!wnd->PollEvents())
		return Hud::MODE::EXIT;

	wndDraw(_curMode);

	DoLogic(_curMode);

	MovePawn(_curMode);
	

	return _curMode;
}

void GameSession::MovePawn(Hud::MODE _curMode)
{
	// if gemeState != PAUSE
	if (_curMode == Hud::MODE::GAME_PROCESS)
	{
		if (timer.CheckInterval(stepTime * speedMyltiply))
			snake->Move();
	}
}

void GameSession::DoLogic(Hud::MODE& _curMode)
{
	if (_curMode != Hud::MODE::GAME_OVER)
	{
		if (!logicField->checkOnEmpty(snake->GetHeadPos()))
		{
			_curMode = Hud::MODE::GAME_OVER;
			wnd->GetHUD().prepButtons(Hud::MODE::GAME_OVER);
		}
		else if (logicField->CheckSnakeGowUp(snake->GetHeadPos()))
		{
			snake->GrowUp();
			++curPoints;
		}
	}
}

void GameSession::wndDraw(Hud::MODE _curMode)
{
	wnd->get().clear();

	switch (_curMode)
	{
	case Hud::MODE::GAME_PROCESS:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->DrawHUD();
		break;

	case Hud::MODE::GAME_PAUSE:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	case Hud::MODE::GAME_OVER:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	default:
		return;
		break;
	}

	wnd->get().display();
}