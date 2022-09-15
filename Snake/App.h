#ifndef APP_H
#define APP_H

#include "MainWindow.h"


class App final
{
private:
	MainWindow wnd;


public:
	App();
	App(const App&)				= delete;
	App& operator=(const App&)	= delete;


	int Run();


private:
	bool isWork		= true;
	bool pause		= false;

};



#endif

