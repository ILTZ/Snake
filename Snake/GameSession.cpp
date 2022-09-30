#include "GameSession.h"

#include "Random.h"
#include <iostream>

GameSession::GameSession(
	MainWin::MainWindow*						_wnd, 
	std::shared_ptr<Base::BasePlayerControlObj> _pawn,
	std::shared_ptr<BaseD>						_gp,
	std::shared_ptr<Logic::LogicField>			_lField,
	std::shared_ptr<BaseD> _apple
	) :
	wnd{_wnd},
	snake{_pawn}, 
	gp{_gp}, 
	logicField{_lField}, 
	apple{_apple},
	stepTime{10.f}, 
	curPoints{0}, 
	speedMyltiply{1.f}, 
	appleOnBoard{false}
{
	
}

GameSession::~GameSession()
{
	snake.reset();
	gp.reset();
}

Hud::MODE GameSession::GameFrame(Hud::MODE _curMode)
{
	// if player press <exit> key on window
	if (!wnd->PollEvents())
		return Hud::MODE::EXIT;

	spawnApple(appleOnBoard);

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
		if (!logicField->checkOnEmpty(snake->GetPos()) || logicField->CheckSnakeCollisions(snake))
		{
			_curMode = Hud::MODE::GAME_OVER;
			wnd->GetHUD().PrepButtons(Hud::MODE::GAME_OVER);
		}
		else if (logicField->CheckSnakeGowUp(snake->GetPos()))
		{
			snake->DoSomeSpecifyActions();
			appleOnBoard = false;
			++curPoints;
		}
	}
}

void GameSession::spawnApple(bool _appleOnBoard)
{
	if (_appleOnBoard)
		return;

	RND::RandomINT rnd;
	unsigned int nul = 0;
	unsigned int x = rnd.GetValue(nul, logicField->GetLVLW() - 1);
	unsigned int y = rnd.GetValue(nul, logicField->GetLVLH() - 1);

	while (!logicField->SetApple(sf::Vector2u(x, y)))
	{
		x = rnd.GetValue(nul, logicField->GetLVLW() - 1);
		y = rnd.GetValue(nul, logicField->GetLVLH() - 1);
	}
	
	apple->SetPos(sf::Vector2u(x, y));
	appleOnBoard = true;
}


void GameSession::wndDraw(Hud::MODE _curMode)
{
	wnd->get().clear();

	switch (_curMode)
	{
	case Hud::MODE::GAME_PROCESS:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->Draw(*apple);
		wnd->DrawHUD();
		break;

	case Hud::MODE::GAME_PAUSE:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->Draw(*apple);
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	case Hud::MODE::GAME_OVER:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->Draw(*apple);
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	default:
		return;
		break;
	}

	wnd->get().display();
}
