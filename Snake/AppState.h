#ifndef APP_STATE_H
#define APP_STATE_H

#include <mutex>

namespace APP_STATE
{
	enum class States
	{
		OPENING			= 0,
		MAIN_MENU		= 1,
		LVL_SELECT		= 2,
		LVL_SELECTED	= 3,
		GAME_PROCESS	= 4,
		GAME_PAUSE		= 5,
		GAME_OVER		= 6,
		LEADERS_VIEW	= 7,
		EXIT			= 8,
	};


	class AppState
	{
	private:
		States currentState = States::OPENING;
		bool switchLock		= false;

	private:
		mutable std::mutex defMutex;

	public:
		AppState() = default;

	public:
		AppState(const AppState&)				= delete;
		AppState(AppState&&)					= delete;

		AppState& operator=(const AppState&)	= delete;
		AppState& operator=(AppState&&)			= delete;

	public:
		States	GetState()					const;
		void	SetState(States _state);

		const bool CheckMainMenuState()		const;
		const bool CheckGameProcessStates()	const;
		const bool CheckMovebleStates()		const;

	public:
		void ExitApp();
		const bool ToExit() const;

	private:

	};

}
#endif

