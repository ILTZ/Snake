#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "MainWindow.h"
#include "Timer.h"
#include "LogicField.h"
#include "BasePlayerControlObj.h"
#include "BaseDrawable.h"

class GameSession
{
private:
	MainWin::MainWindow*							wnd			= nullptr;
	std::shared_ptr<Base::BasePlayerControlObj>		snake;
	std::shared_ptr<BaseD>							gp;
	std::shared_ptr<Logic::LogicField>				logicField;
	std::shared_ptr<BaseD>							apple;

private:
	Timer	timer;
	float	stepTime;
	float	speedMyltiply;

private:
	unsigned int	curPoints;
	bool			appleOnBoard;

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

