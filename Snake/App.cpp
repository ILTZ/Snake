#include "App.h"

App::App()
{
}

int App::Run()
{
	while (isWork)
	{
		while (!pause)
		{
			if (!wnd.PollEvents())
				return 0;

			wnd.Draw();
		}
	}


	return 1;
}
