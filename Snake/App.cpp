#include "App.h"

#include "ScaleDeterminant.h"
#include "ConfigLoader.h"

#include "Apple.h"
#include "SnakeBody.h"

#include "GraphicField.h"
#include "LogicField.h"

#include "HUD.h"

#include <thread>

App::App() 
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	// Window configurate {
	auto configs = loader->GetHudConfigs();
	auto style = sf::Style::Titlebar | sf::Style::Close;

	wnd = std::make_unique<MainWin::MainWindow>(
		configs.width, 
		configs.height, 
		"Snake2D", 
		style);// Window configurate }
	

	// Hud configurate {
	SmartPointer::SmartPointer<ScaleDeterminant> det = new ScaleDeterminant();

	auto hud = std::make_shared<Hud::HUD>(
		configs.pathToHud.c_str(), 
		configs.pathToReleaseBtn.c_str(), 
		configs.pathToPressBtn.c_str(), 
		configs.pathToTextFont.c_str());
	
	auto hudScale = det->CalculateAbsoluteScale(hud->GetHUDSize(), 
		sf::Vector2u(configs.width / 4, 
			configs.height));

	hud->SetScale(hudScale);
	hud->PrepButtons(APP_STATE::States::MAIN_MENU);// Hud configurate }
	

	wnd->SetHud(hud);
	handler.SetHud(hud);

	appState.SetState(APP_STATE::States::MAIN_MENU);
}

int App::Run()
{
	std::jthread t([&]() {
		handleEvents();
		});

	
	while (!appState.ToExit())
	{
		wndProcesses();
		if (appState.GetState() == APP_STATE::States::LVL_SELECTED)
		{
			auto session = createGameSession();
			appState.SetState(APP_STATE::States::GAME_PROCESS);

			while (appState.CheckGameProcessStates())
			{
				session->GameFrame(appState);
			}
		}
	}

	return 0;
}


std::unique_ptr<GameSession> App::createGameSession()
{
	std::lock_guard<std::mutex> lk(defMt);

	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();
	
	auto level = loader->GetLVL(lvlSelected);
	auto sp = loader->GetSnakeProp();

	// Snake {
	auto snake = std::make_shared<Snake::SnakeBody>(
		sp.pathToHead.c_str(),
		sp.pathToTorso.c_str());

	snake->SetPos(sf::Vector2u(
		level->GetConfigs().startPosX,
		level->GetConfigs().startPosY)); // Snake }

	handler.SetPawn(snake);

	auto gf		= std::make_shared<GraphicField::GraphicField>(level);
	auto lf		= std::make_shared<Logic::LogicField>(level, snake);
	auto apple	= std::make_shared<Apple>(sp.pathToAple.c_str());

	// Rescale all game objects {
	SmartPointer::SmartPointer<ScaleDeterminant> det = new ScaleDeterminant(
		sf::Vector2u(wnd->get().getSize().x / 4 * 3, wnd->get().getSize().y),
		sf::Vector2u(level->GetConfigs().width, level->GetConfigs().height));

	gf->CalculateAndSetScale(*det);
	snake->CalculateAndSetScale(*det);
	apple->CalculateAndSetScale(*det); // Rescale all game objects }

	return std::make_unique<GameSession>(wnd.get(), snake, gf, lf, apple);
}

void App::handleEvents()
{
	while (!appState.ToExit())
	{
		handler.HandleKeyEvent(wnd->GetKeyboardEvent(), appState);


		std::lock_guard<std::mutex> lk(defMt);

		auto resM = handler.HandleMouseEvent(wnd->GetMouseEvent(), appState);
		if (resM.has_value())
			lvlSelected = resM.value();
	}
}

void App::wndProcesses()
{
	if (!wnd->PollEvents()) // .. if player press <EXIT> key on window
	{
		appState.ExitApp();
		return;
	}

	drawMenu();
}

void App::drawMenu()
{
	wnd->get().clear();

	switch (appState.GetState())
	{
	case APP_STATE::States::MAIN_MENU:
		wnd->DrawButtons();
		break;

	case APP_STATE::States::LVL_SELECT:
		wnd->DrawButtons();
		break;

	case APP_STATE::States::LEADERS_VIEW:
		wnd->DrawButtons();
		break;

	case APP_STATE::States::EXIT:
		return;
		break;

	default:
		break;
	}

	wnd->get().display();
}



