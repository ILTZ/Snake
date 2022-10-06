#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "MainWindow.h"
#include "Timer.h"
#include "LogicField.h"
#include "BasePlayerControlObj.h"
#include "BaseDrawable.h"

#include "ScoreWidget.h"
#include "TimeWidget.h"
#include "SpeedWidget.h"

class GameSession
{
private:
	MainWin::MainWindow*							wnd			= nullptr;
	std::shared_ptr<Base::BasePlayerControlObj>		snake;
	std::shared_ptr<BaseD>							gp;
	std::shared_ptr<Logic::LogicField>				logicField;
	std::shared_ptr<BaseD>							apple;

	std::shared_ptr<ScoreWidget>	scoreWidget;
	std::shared_ptr<TimeWidget>		timeWidget;
	std::shared_ptr<SpeedWidget>	speedWidget;

private:
	Timer	timer;
	float			stepTime				= 0.75f;
	float			speedMyltiply			= 1.f;
	const float		botBorderSpeedMultiply	= 0.25f;
	float			deltaSpeed				= 0.25f;

private:
	unsigned int	curPoints		= 0u;
	bool			appleOnBoard	= false;

private:
	bool pause = false;

public:
	GameSession(
		MainWin::MainWindow*						_wnd, 
		std::shared_ptr<Base::BasePlayerControlObj> _pawn,
		std::shared_ptr<BaseD>						_gp,
		std::shared_ptr<Logic::LogicField>			_lField,
		std::shared_ptr<BaseD>						_apple);

	~GameSession();

public:
	GameSession(const GameSession&)				= delete;
	GameSession operator=(const GameSession&)	= delete;

public:
	Hud::MODE GameFrame(Hud::MODE _curMode);

private:
	void MovePawn(Hud::MODE _curMode);
	void DoLogic(Hud::MODE& _curMode);

private:
	// Chouse the position of <Apple> and set it coords on the <LogicField>
	void spawnApple(bool _appleOnBoard);

private:
	void wndDraw(Hud::MODE _curMode);
};


#endif

