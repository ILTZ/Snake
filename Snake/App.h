#ifndef APP_H
#define APP_H

#include "MainWindow.h"
#include "GameSession.h"
#include "EventHandler.h"
#include "AppState.h"

using namespace MainWin;

class App final
{
private:
	std::unique_ptr<MainWindow> wnd;
	EventHandler				handler;

private:
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
	std::unique_ptr<GAME_SESSION::GameSession> createGameSession();

private:
	void handleEvents();

private:
	void wndProcesses();
	void drawMenu();

};



#endif

