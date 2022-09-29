#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "MainWindow.h"
#include "SnakeBody.h"
#include "Timer.h"
#include "GraphicField.h"
#include "LogicField.h"

class GameSession
{
private:
	MainWin::MainWindow*						wnd			= nullptr;
	std::shared_ptr<Snake::SnakeBody>			snake;
	std::shared_ptr<GraphicField::GraphicField> gp;
	std::shared_ptr<Logic::LogicField>			logicField;

private:
	Timer timer;
	float stepTime;

private:
	unsigned int curPoints;
	float speedMyltiply;

public:
	GameSession(MainWin::MainWindow* _wnd, 
		std::shared_ptr<Snake::SnakeBody> _pawn,
		std::shared_ptr<GraphicField::GraphicField> _gp,
		std::shared_ptr<Logic::LogicField> _lField);

	~GameSession();

public:
	GameSession(const GameSession&) = delete;
	GameSession operator=(const GameSession&) = delete;

public:
	Hud::MODE GameFrame(Hud::MODE _curMode);

private:
	void MovePawn(Hud::MODE _curMode);
	void DoLogic(Hud::MODE& _curMode);

private:
	void wndDraw(Hud::MODE _curMode);
};


#endif

