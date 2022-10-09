#include "GameSession.h"

#include "Random.h"
#include "ConfigLoader.h"

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
	apple{_apple}
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();
	auto configs = loader->GetHudConfigs();


	scoreWidget = std::make_shared<ScoreWidget>(
		configs.pathToBaseWidget.c_str(),
		configs.pathToTextFont.c_str());

	timeWidget = std::make_shared<TimeWidget>(
		configs.pathToBaseWidget.c_str(),
		configs.pathToTextFont.c_str(),
		1.f);

	speedWidget = std::make_shared<SpeedWidget>(
		configs.pathToBaseWidget.c_str(),
		configs.pathToTextFont.c_str()
		);

	_wnd->GetHUD().AddWidget(scoreWidget);
	_wnd->GetHUD().AddWidget(speedWidget);
	_wnd->GetHUD().AddWidget(timeWidget);
}

GameSession::~GameSession()
{
	snake.reset();
	gp.reset();
	wnd->GetHUD().ClearWidgets();
}

void GameSession::GameFrame(APP_STATE::AppState& _state)
{
	// if player press <exit> key on window
	if (!wnd->PollEvents())
	{
		_state.ExitApp();
		return;
	}

	spawnApple(appleOnBoard);

	wndDraw(_state);

	DoLogic(_state);

	MovePawn(_state);
	
}

void GameSession::MovePawn(const APP_STATE::AppState& _state)
{
	// if gemeState != PAUSE
	if (_state.GetState() == APP_STATE::States::GAME_PROCESS)
	{
		timeWidget->WorkCycle(!pause);
		if (timer.CheckInterval(stepTime * speedMyltiply))
			snake->Move();
	}
}

void GameSession::DoLogic(APP_STATE::AppState& _state)
{
	if (_state.GetState() != APP_STATE::States::GAME_OVER)
	{
		if (!logicField->checkOnEmpty(snake->GetPos()) || logicField->CheckSnakeCollisions())
		{
			_state.SetState(APP_STATE::States::GAME_OVER);
			wnd->GetHUD().PrepButtons(Hud::MODE::GAME_OVER);
		}
		else if (logicField->CheckSnakeGowUp(snake->GetPos()))
		{
			snake->DoSomeSpecifyActions();
			appleOnBoard = false;
			++curPoints;
			scoreWidget->IncreaseScores();

			if (speedMyltiply <= (botBorderSpeedMultiply + botBorderSpeedMultiply / 2.f))
				return; // No more speed

			if (curPoints > 0u && (curPoints % appleBorder == 0u))
			{
				speedMyltiply -= deltaSpeed;
				speedWidget->IncreaseViewSpeed(deltaSpeed);
			}

		}
	}
}

void GameSession::spawnApple(bool _appleOnBoard)
{
	if (_appleOnBoard)
		return;

	RND::RandomINT rnd;
	const unsigned int nul = 0;
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

void GameSession::wndDraw(const APP_STATE::AppState& _state)
{
	wnd->get().clear();

	switch (_state.GetState())
	{
	case APP_STATE::States::GAME_PROCESS:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->Draw(*apple);
		wnd->DrawHUD();
		break;

	case APP_STATE::States::GAME_PAUSE:
		wnd->Draw(*gp);
		wnd->Draw(*snake);
		wnd->Draw(*apple);
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	case APP_STATE::States::GAME_OVER:
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
