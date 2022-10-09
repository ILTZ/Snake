#ifndef APP_H
#define APP_H

#include "MainWindow.h"
#include "SnakeBody.h"
#include "GraphicField.h"
#include "HUD.h"
#include "EventHandler.h"
#include "Timer.h"
#include "ConfigLoader.h"
#include "GameSession.h"
#include "Apple.h"
#include "AppState.h"


using namespace MainWin;

class App final
{
private:
	std::unique_ptr<MainWindow> wnd;
	EventHandler				handler;

private:
	Hud::MODE		currentMode;
	APP_STATE::AppState appState;

private:
	CLoader::LVLs	lvlSelected;

private:
	std::mutex		defMt;

public:
	App();

public:
	App(const App&)				= delete;
	App& operator=(const App&)	= delete;

public:
	int Run();

private:
	std::unique_ptr<GameSession> createGameSession();

private:
	void handleEvents();

private:
	void wndProcesses();
	void drawMenu();

private:
	void setCurMode(Hud::MODE _mode);

};



#endif

