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


using namespace MainWin;

class App final
{
private:
	std::unique_ptr<MainWindow> wnd;
	EventHandler handler;

private:
	Timer time;
	Hud::MODE currentMode;
	
private:
	CLoader::LVLs lvlSelected;

private:
	std::mutex defMt;

public:
	App();

public:
	App(const App&)				= delete;
	App& operator=(const App&)	= delete;

public:
	int Run();

private:
	// 1 sec
	float stepTime = 1000.f;

private:
	std::unique_ptr<GameSession> getGameSession();

private:
	void handleEvents();

private:
	void wndProcesses();
	void drawMenu();

	std::shared_ptr<Snake::SnakeBody> prepareSnake(const char* _pTh, const char* _pTt, auto _lvl);
	std::shared_ptr<GraphicField::GraphicField> prepareGraphicField(auto _lvl);
	std::shared_ptr<Hud::HUD> createHUD(const char* _pathToHud, const char* _pathToBtnReleased, 
		const char* _pathToBtnPressed, const char* _pathToFont);

private:
	void setCurMode(Hud::MODE _mode);
};



#endif

