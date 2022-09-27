#include "App.h"
#include "LogicField.h"

#include <iostream>
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

	handler.SetHud(hud);
}

int App::Run()
{
	std::jthread t([&]() {
		handleEvents();
		});

	
	while (currentMode != Hud::MODE::EXIT)
	{
		wndProcesses();
		if (currentMode == Hud::MODE::LVL_SELECTED)
		{
			auto session = getGameSession();
			setCurMode(Hud::MODE::GAME_PROCESS);

			while (currentMode != Hud::MODE::MAIN_MENU && currentMode != Hud::MODE::EXIT)
			{
				if (!session->GameFrame(currentMode))
				{
					setCurMode(Hud::MODE::EXIT);
					return 1;
				}
			}
		}
	}

	return 0;
}


std::unique_ptr<GameSession> App::getGameSession()
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	auto level = loader->GetLVL(lvlSelected);

	auto snake = prepareSnake(loader->GetPathTo(CLoader::ConfigKey::SNAKE_H).c_str(),
		loader->GetPathTo(CLoader::ConfigKey::SNAKE_T).c_str(), level);
	handler.SetPawn(snake);

	auto gf = prepareGraphicField(level);

	auto lf = std::make_shared<Logic::LogicField>(level);

	return std::make_unique<GameSession>(wnd.get(), snake, gf, lf);
}

void App::handleEvents()
{
	while (currentMode != Hud::MODE::EXIT)
	{
		auto resK = handler.HandleKeyEvent(wnd->GetKeyboardEvent(), currentMode);
		auto resM = handler.HandleMouseEvent(wnd->GetMouseEvent(), currentMode);

		if (resK.has_value())
			setCurMode(resK.value());

		if (resM.has_value())
		{
			if (resM.value().gameMode == Hud::MODE::LVL_SELECTED) 
				lvlSelected = resM.value().lvl;
			setCurMode(resM.value().gameMode);
		}
	}
}




void App::wndProcesses()
{
	if (!wnd->PollEvents()) // .. if player press <EXIT> key on window
	{
		setCurMode(Hud::MODE::EXIT);
		return;
	}

	std::lock_guard<std::mutex> lk(defMt);
	drawMenu();
}

void App::drawMenu()
{
	wnd->get().clear();

	switch (currentMode)
	{
	case Hud::MODE::MAIN_MENU:
		wnd->DrawButtons();
		break;

	case Hud::MODE::LVL_SELECT:
		wnd->DrawButtons();
		break;

	case Hud::MODE::LEADERS:
		wnd->DrawButtons();
		break;

	case Hud::MODE::EXIT:
		return;
		break;

	default:
		break;
	}

	wnd->get().display();

}

std::shared_ptr<Snake::SnakeBody> App::prepareSnake(const char* _pTh, const char* _pTt, auto _lvl)
{
	auto snake = std::make_shared<Snake::SnakeBody>(_pTh, _pTt);

	snake->SetSpriteScale(wnd->get().getSize().x, wnd->get().getSize().y,
		_lvl->GetConfigs().width, _lvl->GetConfigs().height);

	snake->SetPos(sf::Vector2u(_lvl->GetConfigs().startPosX,
		_lvl->GetConfigs().startPosY));

	return snake;
}

std::shared_ptr<GraphicField::GraphicField> App::prepareGraphicField(auto _lvl)
{
	auto gf = std::make_shared<GraphicField::GraphicField>(_lvl);

	gf->SetSpriteScale(wnd->get().getSize().x, wnd->get().getSize().y,
		_lvl->GetConfigs().width, _lvl->GetConfigs().height);

	return gf;
}

std::shared_ptr<Hud::HUD> App::createHUD(const char* _pathToHud, const char* _pathToBtnReleased, 
	const char* _pathToBtnPressed, const char* _pathToFont)
{
	return std::make_shared<Hud::HUD>(_pathToHud, _pathToBtnReleased, _pathToBtnPressed, _pathToFont);
}

void App::setCurMode(Hud::MODE _mode)
{
	std::lock_guard<std::mutex> lk(defMt);

	currentMode = _mode;
}
