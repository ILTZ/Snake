#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Keyboard.h"
#include "Mouse.h"

#include "HUD.h"
#include "BasePawn.h"

#include "ConfigLoader.h"

#include "AppState.h"

class EventHandler
{
public:
	struct HandleResult
	{
		APP_STATE::States		gameMode;
		LVLConstructor::LVLs	lvl;
	};

private:
	std::shared_ptr<UI::Ui>				hud;
	std::shared_ptr<BaseP::BasePawn>	pawn;

private:
	std::mutex defMt;

public:
	EventHandler() = default;
	EventHandler(
		std::shared_ptr<UI::Ui> _hud, 
		std::shared_ptr<BaseP::BasePawn> _snakePawn);

public:
	EventHandler(const EventHandler&)				= delete;
	EventHandler& operator=(const EventHandler&)	= delete;

public:
	void SetPawn(std::shared_ptr<BaseP::BasePawn> _pawn);
	void SetHud(std::shared_ptr<UI::Ui> _hud);

public:
	void						HandleKeyEvent(
		const std::optional<Keyboard::KeyEvent>&_keyEvent, 
		APP_STATE::AppState& _state);

	void						HandleCharEvent(
		const std::optional<Keyboard::TextEvent>& _keyEvent,
		APP_STATE::AppState& _state);

	std::optional<LVLConstructor::LVLs> HandleMouseEvent(
		const std::optional<MS::MouseEvent>& _mouseEvent, 
		APP_STATE::AppState& _state);

public:
	void FlushBasePawn();

private:

};

#endif
