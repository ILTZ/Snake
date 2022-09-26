#include "App.h"
#include <thread>

App::App() : currentMode{Hud::MODE::MAIN_MENU}
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	// Window prop {
	auto configs = loader->GetHudConfigs();
	auto style = sf::Style::Titlebar | sf::Style::Close;

	wnd = std::make_unique<MainWin::MainWindow>
		(configs.width, configs.height, "Snake2D", style);
	// Window prop }

	auto hud = createHUD(configs.pathToHud.c_str(), configs.pathToReleaseBtn.c_str(), 
		configs.pathToPressBtn.c_str(), configs.pathToTextFont.c_str());
	hud->SetSpriteScale(wnd->get().getSize().x, wnd->get().getSize().y);

	wnd->SetHud(hud);

	handler = new EventHandler();
	handler->SetHud(hud);
}

int App::Run()
{
	/*while (isWork)
	{
		prepareBeforeStart();
		while (!pause)
		{
			if (!wnd->PollEvents())
				return 0;

			wnd->get().clear();

			wnd->DrawLayouts();
			wnd->DrawHUD();
			wnd->DrawButtons();

			wnd->get().display();

		}
	}*/

	std::jthread t([&]() {
		handleEvents();
		});

	DrawProcess();
	

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

	prepWindow(snake, gf);
}

void App::handleEvents()
{
	while (currentMode != Hud::MODE::EXIT)
	{
		auto resK = handler->HandleKeyEvent(wnd->GetKeyboardEvent(), currentMode);
		auto resM = handler->HandleMouseEvent(wnd->GetMouseEvent(), currentMode);

		if (resK.has_value())
			currentMode = resK.value();

		if (resM.has_value())
			currentMode = resM.value();

	}
}

bool App::prepWindow(auto _snake, auto _field)
{
	wnd->AddToDrawLayout(_snake, Plans::FIRST_PLAN);
	wnd->AddToDrawLayout(_field, Plans::SECOND_PLAN);

	return true;
}

bool App::prepLogicField(auto _snake, auto _field)
{
	return false;
}

void App::DrawProcess()
{
	while (currentMode != Hud::MODE::EXIT)
	{
		if (!wnd->PollEvents())
		{
			currentMode = Hud::MODE::EXIT;

			return;
		}

		drawFormMode();
	}

	
}

void App::drawFormMode()
{
	wnd->get().clear();

	switch (currentMode)
	{
	case Hud::MODE::MAIN_MENU:
		wnd->DrawButtons();
		break;

	case Hud::MODE::LVL_CHOISE:
		wnd->DrawButtons();
		break;

	case Hud::MODE::GAME_PROCESS:
		wnd->DrawLayouts();
		wnd->DrawHUD();
		break;

	case Hud::MODE::GAME_PAUSE:
		wnd->DrawLayouts();
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	case Hud::MODE::GAME_OVER:
		wnd->DrawLayouts();
		wnd->DrawHUD();
		wnd->DrawButtons();
		break;

	case Hud::MODE::LEADERS:

		break;

	case Hud::MODE::EXIT:
		return;
		break;

	default:
		break;
	}

	wnd->get().display();

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
