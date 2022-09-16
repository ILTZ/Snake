#include "App.h"

#include "ConfigLoader.h"

App::App()
{
	using namespace CLoader;
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	snake = std::make_unique<Snake::SnakeBody>(loader->GetPathTo(ConfigKey::SNAKE_H).c_str(), loader->GetPathTo(ConfigKey::SNAKE_T).c_str());

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
