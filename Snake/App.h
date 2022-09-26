#ifndef APP_H
#define APP_H

#include "MainWindow.h"
#include "SnakeBody.h"
#include "GraphicField.h"
#include "HUD.h"
#include "EventHandler.h"

#include "ConfigLoader.h"

using namespace MainWin;

class App final
{
private:
	std::unique_ptr<MainWindow> wnd;
	SmartPointer::SmartPointer<EventHandler> handler;

private:


public:
	App();

public:
	App(const App&)				= delete;
	App& operator=(const App&)	= delete;

public:
	int Run();

private:
	bool isWork		= true;
	bool pause		= false;

private:
	Hud::MODE currentMode;

private:
	void prepareBeforeStart(CLoader::LVLs _level = CLoader::LVLs::LVL_1);

private:
	void handleEvents();

private:
	bool prepWindow(auto _snake, auto _field);
	bool prepLogicField(auto _snake, auto _field);

	void DrawProcess();
	void drawFormMode();

	std::shared_ptr<Snake::SnakeBody> createSnake(const char* _pTh, const char* _pTt);
	std::shared_ptr<GraphicField::GraphicField> createGraphicField(auto _lvl);
	std::shared_ptr<Hud::HUD> createHUD(const char* _pathToHud, const char* _pathToBtnReleased, 
		const char* _pathToBtnPressed, const char* _pathToFont);

};



#endif

