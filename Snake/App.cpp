#include "App.h"

App::App()
{

}

int App::Run()
{
	while (isWork)
	{
		prepareBeforeStart();
		while (!pause)
		{
			if (!wnd.PollEvents())
				return 0;

			

			wnd.Draw();
		}
	}


	return 1;
}

void App::prepareBeforeStart(CLoader::LVLs _level)
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	auto snake = std::make_shared<Snake::SnakeBody>
		(loader->GetPathTo(CLoader::ConfigKey::SNAKE_H).c_str(),
			loader->GetPathTo(CLoader::ConfigKey::SNAKE_T).c_str());

	auto level = loader->GetLVL(_level);

	snake->SetPos(sf::Vector2f((float)level->GetConfigs().startPosX, 
		(float)level->GetConfigs().startPosY));

	prepWindow(snake, createGraphicField(level));
}

bool App::prepWindow(auto _snake, auto _field)
{
	wnd.AddToDrawLayout(_snake, Plans::FIRST_PLAN);
	wnd.AddToDrawLayout(_field, Plans::SECOND_PLAN);

	return true;
}

bool App::prepLogicField(auto _snake, auto _field)
{
	return false;
}

std::shared_ptr<Snake::SnakeBody> App::createSnake(const char* _pTh, const char* _pTt)
{
	return std::make_shared<Snake::SnakeBody>(_pTh, _pTt);
}

std::shared_ptr<GraphicField::GraphicField> App::createGraphicField(auto _lvl)
{
	return std::make_shared<GraphicField::GraphicField>(_lvl);
}
