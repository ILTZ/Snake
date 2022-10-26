#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "MainWindow.h"
#include "Timer.h"
#include "LogicField.h"
#include "BasePlayerControlObj.h"

#include "ScoreWidget.h"
#include "TimeWidget.h"
#include "SpeedWidget.h"

#include "AppState.h"
#include "Apple.h"

namespace GAME_SESSION
{
	struct GameSessionResults
	{
		GameSessionResults(
			const char* _name, 
			unsigned int _points, 
			unsigned int _minuts, 
			unsigned int _seconds);

		const std::string		playerName;
		const unsigned int		points;

		const unsigned int		minuts;
		const unsigned int		seconds;
	};

	class GameSession
	{
	private:
		MainWin::MainWindow*							wnd			= nullptr;
		std::shared_ptr<Base::BasePlayerControlObj>		snake;
		std::shared_ptr<BaseDrawable>					gp;
		std::shared_ptr<Logic::LogicField>				logicField;
		std::shared_ptr<Apple>					apple;

		std::shared_ptr<ScoreWidget>	scoreWidget;
		std::shared_ptr<TimeWidget>		timeWidget;
		std::shared_ptr<SpeedWidget>	speedWidget;

	private:
		Timer	timer;
		float			stepTime				= 0.75f;
		float			speedMyltiply			= 1.f;
		const float		botBorderSpeedMultiply	= 0.25f;
		float			deltaSpeed				= 0.25f;
		unsigned int	appleBorder				= 20u;

	private:
		unsigned int	curPoints		= 0u;
		bool			appleOnBoard	= false;

	private:
		bool pause = false;

	public:
		GameSession(
			MainWin::MainWindow*						_wnd, 
			std::shared_ptr<Base::BasePlayerControlObj> _pawn,
			std::shared_ptr<BaseDrawable>				_gp,
			std::shared_ptr<Logic::LogicField>			_lField,
			std::shared_ptr<Apple>						_apple);

		~GameSession();

	public:
		GameSession(const GameSession&)				= delete;
		GameSession operator=(const GameSession&)	= delete;

	public:
		std::optional<GameSessionResults> GameProcess(APP_STATE::AppState& _state);
		

	private:
		void MovePawn(const APP_STATE::AppState& _state);
		void DoLogic(APP_STATE::AppState& _state);

	private:
		const std::optional<GameSessionResults> FormGameSessionResults() const;

	private:
		// Chouse the position of <Apple> and set it coords on the <LogicField>
		void spawnApple(bool _appleOnBoard);

	private:
		void wndDraw(const APP_STATE::AppState& _state);
	};

}
#endif

