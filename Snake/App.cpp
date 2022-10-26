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
#include <Windows.h>

App::App() 
{
	loader = new CLoader::Loader();

	CLoader::WndConfigs wndConfigs;
	CLoader::HudConfigs cfg;

	// Its required data. 
	try
	{
		wndConfigs	= loader->GetWndConfigs();
		cfg			= loader->GetHudPaths();
	}
	catch (CLoader::Loader::JsonParseException& _ex)
	{
		throw _ex;
	}
	catch (CLoader::Loader::LoaderException& _ex)
	{
		throw _ex;
	} // Without them there is no point in running the application

	
	auto style = sf::Style::Titlebar | sf::Style::Close;

	wnd = std::make_unique<MainWin::MainWindow>(
		wndConfigs.width, 
		wndConfigs.height,
		"Snake2D", 
		style);
	

	SmartPointer::SmartPointer<ScaleDeterminant> det = new ScaleDeterminant();

	auto hud = std::make_shared<UI::Ui>(cfg);

	auto hudScale = det->CalculateAbsoluteScale(
		hud->GetHUDSize(), 
		wnd->GetHudTargetSize());

	hud->SetScale(hudScale);
	hud->PrepButtons(APP_STATE::States::MAIN_MENU);
	

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
			if (session.get())
			{
				wnd->GetHUD().ClearBtnsLogicArr();
				wnd->GetHUD().ClearMainLayout();

				appState.SetState(APP_STATE::States::GAME_PROCESS);

				auto result = session->GameProcess(appState);

				if (result.has_value())
					loader->AddLeaderInLeaderBord(
						result.value().playerName.c_str(),
						result.value().points,
						result.value().minuts,
						result.value().seconds);

				handler.FlushBasePawn();
			}
			else
			{
				appState.SetState(APP_STATE::States::MAIN_MENU);
				wnd->GetHUD().PrepButtons(appState.GetState());
			}
		}
	}

	handlingThread.join();

	return 0;
}


std::unique_ptr<GAME_SESSION::GameSession> App::createGameSession()
{
	std::lock_guard<std::mutex> lk(defMt);
	
	std::shared_ptr<LVLConstructor::Level>	level;
	CLoader::SnakePaths						sp;

	try
	{
		level	= loader->GetLVL(lvlSelected);
		sp		= loader->GetSnakePaths();
	}
	catch (BaseException& _ex)
	{
		MessageBoxA(nullptr, _ex.what(), _ex.GetType(), MB_OK | MB_ICONERROR);
		return nullptr;
	} // Why play if you don't have all the assets?
	
	#pragma region Snake_creating
	//
	auto snake = std::make_shared<Snake::SnakeBody>(
		sp.pathToHead.c_str(),
		sp.pathToTorso.c_str());

	snake->SetStartPos(sf::Vector2u(
		level->GetConfigs().startPosX,
		level->GetConfigs().startPosY));
	//
	#pragma endregion

	handler.SetPawn(snake);

	auto gf		= std::make_shared<GraphicField::GraphicField>(level);
	auto lf		= std::make_shared<Logic::LogicField>(level, snake);
	auto apple	= std::make_shared<Apple>(sp.pathToAple.c_str());

	#pragma region Rescale_game_objects
	//
	SmartPointer::SmartPointer<ScaleDeterminant> det = new ScaleDeterminant(
		wnd->GetGameFieldTargetSize(),
		sf::Vector2u(level->GetConfigs().width, level->GetConfigs().height));

	gf->CalculateAndSetScale(*det);
	snake->CalculateAndSetScale(*det);
	apple->CalculateAndSetScale(*det);
	//
	#pragma endregion

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

	wnd->get().clear();
	wnd->DrawUI(appState.GetState());
	wnd->get().display();
}

void App::drawMenu()
{
	
}



