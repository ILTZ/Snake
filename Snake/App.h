#ifndef APP_H
#define APP_H

#include "MainWindow.h"
#include "SnakeBody.h"
#include "GraphicField.h"
#include "ConfigLoader.h"

using namespace MainWin;

class App final
{
private:
	std::unique_ptr<MainWindow> wnd;

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
	void prepareBeforeStart(CLoader::LVLs _level = CLoader::LVLs::LVL_1);

private:
	bool prepWindow(auto _snake, auto _field);
	bool prepLogicField(auto _snake, auto _field);


	std::shared_ptr<Snake::SnakeBody> createSnake(const char* _pTh, const char* _pTt);
	std::shared_ptr<GraphicField::GraphicField> createGraphicField(auto _lvl);

};



#endif

