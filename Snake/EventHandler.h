#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Keyboard.h"
#include "Mouse.h"

#include "HUD.h"
#include "BasePawn.h"


class EventHandler
{
private:
	std::shared_ptr<Hud::HUD>			hud;
	std::shared_ptr<BaseP::BasePawn>	pawn;


public:
	EventHandler() = default;
	EventHandler(std::shared_ptr<Hud::HUD> _hud, std::shared_ptr<BaseP::BasePawn> _snakePawn);

public:
	EventHandler(const EventHandler&) = delete;
	EventHandler& operator=(const EventHandler&) = delete;

public:
	void SetPawn(std::shared_ptr<BaseP::BasePawn> _pawn);
	void SetHud(std::shared_ptr<Hud::HUD> _hud);

public:
	std::optional<Hud::MODE> HandleKeyEvent(const std::optional<KB::KeyEvent>&_keyEvent, Hud::MODE _mode);
	std::optional<Hud::MODE> HandleMouseEvent(const std::optional<MS::MouseEvent>& _mouseEvent, Hud::MODE _mode);

private:

};

#endif
