#include "App.h"

#include "ScaleDeterminant.h"
#include "ConfigLoader.h"

#include "Apple.h"
#include "SnakeBody.h"

#include "GraphicField.h"
#include "LogicField.h"

#include "HUD.h"

#include <SFML/System/Thread.hpp>
#include <thread>

App::App() 
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();

	// Window configurate {
	auto style = sf::Style::Titlebar | sf::Style::Close;
	auto wndConfigs = loader->GetWndConfigs();

	wnd = std::make_unique<MainWin::MainWindow>(
		wndConfigs.width, 
		wndConfigs.height,
		"Snake2D", 
		style);// Window configurate }
	

	// Hud configurate {
	SmartPointer::SmartPointer<ScaleDeterminant> det = new ScaleDeterminant();

	auto configs = loader->GetHudPaths();
	auto hud = std::make_shared<Hud::HUD>(configs);

	auto hudScale = det->CalculateAbsoluteScale(
		hud->GetHUDSize(), 
		wnd->GetHudTargetSize());

	hud->SetScale(hudScale);
	hud->PrepButtons(APP_STATE::States::MAIN_MENU);// Hud configurate }
	

	wnd->SetHud(hud);
	handler.SetHud(hud);

	appState.SetState(APP_STATE::States::MAIN_MENU);
}

int App::Run()
{
	std::thread handlingThread([&]() {
		handleEvents();
		});

	while (!appState.ToExit())
	{
		wndProcesses();
		if (appState.GetState() == APP_STATE::States::LVL_SELECTED)
		{
			auto session = createGameSession();
			appState.SetState(APP_STATE::States::GAME_PROCESS);

			auto result = session->GameProcess(appState);

		}
	}

	handlingThread.join();

	return 0;
}


std::unique_ptr<GAME_SESSION::GameSession> App::createGameSession()
{
	std::lock_guard<std::mutex> lk(defMt);

	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();
	
	auto level = loader->GetLVL(lvlSelected);
	auto sp = loader->GetSnakePaths();

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
		wnd->GetGameFieldTargetSize(),
		sf::Vector2u(level->GetConfigs().width, level->GetConfigs().height));

	gf->CalculateAndSetScale(*det);
	snake->CalculateAndSetScale(*det);
	apple->CalculateAndSetScale(*det); // Rescale all game objects }

	

	return std::make_unique<GAME_SESSION::GameSession>(wnd.get(), snake, gf, lf, apple);
}

void App::handleEvents()
{
	while (!appState.ToExit())
	{
		handler.HandleKeyEvent(wnd->GetKeyboardEvent(), appState);
		handler.HandleCharEvent(wnd->GetTextEvent(), appState);

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



