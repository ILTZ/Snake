#include "App.h"

App::App()
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	// Window prop {
	const std::pair resolution{ loader->GetResolution() };
	auto style = sf::Style::Titlebar | sf::Style::Close;

	wnd = std::make_unique<MainWin::MainWindow>
		(resolution.first, resolution.second, "Snake2D", style);
	// Window prop }
}

int App::Run()
{
	while (isWork)
	{
		prepareBeforeStart();
		while (!pause)
		{
			if (!wnd->PollEvents())
				return 0;

			

			wnd->Draw();
		}
	}


	return 1;
}

void App::prepareBeforeStart(CLoader::LVLs _level)
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	auto level = loader->GetLVL(_level);

	auto snake = std::make_shared<Snake::SnakeBody>
		(loader->GetPathTo(CLoader::ConfigKey::SNAKE_H).c_str(),
			loader->GetPathTo(CLoader::ConfigKey::SNAKE_T).c_str());
	snake->SetPos(sf::Vector2f((float)level->GetConfigs().startPosX, 
		(float)level->GetConfigs().startPosY));
	snake->SetSpriteScale(wnd->get().getSize().x, wnd->get().getSize().y,
		level->GetConfigs().width, level->GetConfigs().height);

	auto gf = createGraphicField(level);
	gf->SetSpriteScale(wnd->get().getSize().x, wnd->get().getSize().y,
		level->GetConfigs().width, level->GetConfigs().height);

	auto hud = createHUD(loader->GetPathTo(CLoader::ConfigKey::HUD).c_str(), loader->GetPathTo(CLoader::ConfigKey::BTN_RELEASE).c_str(),
		loader->GetPathTo(CLoader::ConfigKey::BTN_PRESS).c_str(), loader->GetPathTo(CLoader::ConfigKey::TEXT_FONT).c_str());
	hud->SetSpriteScale(wnd->get().getSize().x, wnd->get().getSize().y, 0, 0);

	prepWindow(snake, gf, hud);
}

bool App::prepWindow(auto _snake, auto _field, auto _hud)
{
	wnd->AddToDrawLayout(_snake, Plans::FIRST_PLAN);
	wnd->AddToDrawLayout(_field, Plans::SECOND_PLAN);
	wnd->AddToDrawLayout(_hud, Plans::HUD);

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

std::shared_ptr<Hud::HUD> App::createHUD(const char* _pathToHud, const char* _pathToBtnReleased, 
	const char* _pathToBtnPressed, const char* _pathToFont)
{
	return std::make_shared<Hud::HUD>(_pathToHud, _pathToBtnReleased, _pathToBtnPressed, _pathToFont);
}
