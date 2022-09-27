#include "GameSession.h"

GameSession::GameSession(MainWin::MainWindow* _wnd, 
	std::shared_ptr<Snake::SnakeBody> _pawn,
	std::shared_ptr<GraphicField::GraphicField> _gp,
	std::shared_ptr<Logic::LogicField> _lField) : 
	wnd{_wnd}, basePawn{_pawn}, gp{_gp}, logicField{_lField},
	stepTime{10.f}, curPoints{0}, speedMyltiply{1.f}
{

}

GameSession::~GameSession()
{
	basePawn.reset();
	gp.reset();
}

int GameSession::GameFrame(Hud::MODE _curMode)
{
	if (!wnd->PollEvents())
		return 0;

	if (!logicField->checkOnEmpty(basePawn->GetHeadPos()))
		return 0;

	if (logicField->CheckSnakeGowUp(basePawn->GetHeadPos()))
	{
		basePawn->GrowUp();
		++curPoints;
	}


	wnd->get().clear();
	wndDraw(_curMode);
	wnd->get().display();

	if (_curMode == Hud::MODE::GAME_PROCESS)
	{
		if (timer.CheckInterval(stepTime * speedMyltiply))
			basePawn->Move();
	}

	return 1;
}

void GameSession::MovePawn()
{
	basePawn->Move();
}

void GameSession::wndDraw(Hud::MODE _curMode)
{
	switch (_curMode)
	{
	case Hud::MODE::GAME_PROCESS:
		wnd->Draw(*gp);
		wnd->Draw(*basePawn);
		wnd->DrawHUD();
		break;

	case Hud::MODE::GAME_PAUSE:
		wnd->Draw(*gp);
		wnd->Draw(*basePawn);
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	case Hud::MODE::GAME_OVER:
		wnd->Draw(*gp);
		wnd->Draw(*basePawn);
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	default:
		return;
		break;
	}
}
