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
		INPUT_NAME		= 6,
		GAME_OVER		= 7,
		LEADERS_VIEW	= 8,
		EXIT			= 9,
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
		const	States GetState()				const noexcept;
		void	SetState(States _state)			noexcept;

		const bool CheckMainMenuState()			const noexcept;
		const bool CheckGameProcessStates()		const noexcept;
		const bool CheckMovebleStates()			const noexcept;
		const bool CheckTabuForLogicStates()	const noexcept;

	public:
		void ExitApp()							noexcept;
		const bool ToExit()						const noexcept;

	private:

	};

}
#endif

