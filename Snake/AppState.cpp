#include "AppState.h"

APP_STATE::States APP_STATE::AppState::GetState() const 
{
	std::lock_guard<std::mutex> lg(defMutex);

    return currentState;
}

void APP_STATE::AppState::SetState(States _state)
{
	if (switchLock)
		return;

	std::lock_guard<std::mutex> lg(defMutex);

    currentState = _state;
}

const bool APP_STATE::AppState::CheckMainMenuState() const
{
	std::lock_guard<std::mutex> lg(defMutex);

	switch (currentState)
	{
	case APP_STATE::States::MAIN_MENU:
	case APP_STATE::States::LVL_SELECT:
	case APP_STATE::States::LVL_SELECTED:
	case APP_STATE::States::LEADERS_VIEW:
		return true;
	}

	return false;
}

const bool APP_STATE::AppState::CheckGameProcessStates() const 
{
	std::lock_guard<std::mutex> lg(defMutex);

	switch (currentState)
	{
	case APP_STATE::States::GAME_PROCESS:
	case APP_STATE::States::GAME_PAUSE:
	case APP_STATE::States::GAME_OVER:
		return true;
	}

    return false;
}

const bool APP_STATE::AppState::CheckMovebleStates() const
{
	std::lock_guard<std::mutex> lg(defMutex);

	if (currentState == States::GAME_PROCESS)
		return true;

	return false;
}

void APP_STATE::AppState::ExitApp()
{
	currentState = States::EXIT;
	switchLock = true;
}

const bool APP_STATE::AppState::ToExit() const
{
	return (currentState == States::EXIT) ? true : false;
}