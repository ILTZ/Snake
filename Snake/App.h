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

using namespace MainWin;

class App final
{
private:
	std::unique_ptr<MainWindow> wnd;
	EventHandler				handler;

private:
	Hud::MODE		currentMode;
	
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
	std::shared_ptr<Snake::SnakeBody> createSnake(
		const char* _pTh, 
		const char* _pTt, 
		auto _lvl)				const;
	std::shared_ptr<Hud::HUD> createHUD(
		const char* _pathToHud, 
		const char* _pathToBtnReleased, 
		const char* _pathToBtnPressed, 
		const char* _pathToFont, 
		unsigned int _width, 
		unsigned int _height)	const;

	std::shared_ptr<Apple> createApple(const char* _pTa, auto _lvl)				const;
	std::shared_ptr<GraphicField::GraphicField> createGrapcfhicField(auto _lvl)	const;

private:
	void setCurMode(Hud::MODE _mode);
	bool checkGameProcessMod(Hud::MODE _gm);
};



#endif

