#include "App.h"

#include "LogicField.h"
#include "ScaleDeterminant.h"

#include <thread>

App::App() : currentMode{Hud::MODE::MAIN_MENU}
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
	hud->PrepButtons(currentMode);
	hud->SetScale(hudScale);// Hud configurate }

	wnd->SetHud(hud);

	handler.SetHud(hud);
}

int App::Run()
{
	std::jthread t([&]() {
		handleEvents();
		});

	
	auto checkGameSessionMods = [](Hud::MODE _mode) -> bool
	{
		switch (_mode)
		{
		case Hud::MODE::GAME_PROCESS:
		case Hud::MODE::GAME_PAUSE:
		case Hud::MODE::GAME_OVER:
			return true;

		default:
			return false;
		}
	};

	while (currentMode != Hud::MODE::EXIT)
	{
		wndProcesses();

		
		if (currentMode == Hud::MODE::LVL_SELECTED) 
		{

			auto session = createGameSession(); // <GameSession> life time is start now {
			setCurMode(Hud::MODE::GAME_PROCESS);

			// May <GameSession> control render process in GAME_PROCESS time
			while (checkGameSessionMods(currentMode))
			{
				auto mode = session->GameFrame(currentMode);

				// difference between threads(<event handler> is faster switch currentMode of app)
				if (currentMode != Hud::MODE::MAIN_MENU &&
					currentMode != Hud::MODE::EXIT &&
					currentMode != Hud::MODE::GAME_PAUSE)
				{
					setCurMode(mode);
				}

			}
		}// <GameSession> life time is end }
	}

	return 0;
}


std::unique_ptr<GameSession> App::createGameSession()
{
	SmartPointer::SmartPointer<CLoader::ConfigLoader> loader = new CLoader::ConfigLoader();
	
	auto level = loader->GetLVL(lvlSelected);

	auto sp = loader->GetSnakeProp();
	auto snake = createSnake(
		sp.pathToHead.c_str(),
		sp.pathToTorso.c_str(), 
		level);
	handler.SetPawn(snake);

	SmartPointer::SmartPointer<ScaleDeterminant> det = new ScaleDeterminant(
		sf::Vector2u(wnd->get().getSize().x / 4 * 3, wnd->get().getSize().y),
		sf::Vector2u(level->GetConfigs().width, level->GetConfigs().height));


	auto gf = createGrapcfhicField(level);
	auto lf = std::make_shared<Logic::LogicField>(level);
	auto apple = createApple(sp.pathToAple.c_str(), level);

	gf->CalculateAndSetScale(*det);
	snake->CalculateAndSetScale(*det);
	apple->CalculateAndSetScale(*det);

	return std::make_unique<GameSession>(wnd.get(), snake, gf, lf, apple);
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

std::shared_ptr<Snake::SnakeBody> App::createSnake(
	const char* _pTh, 
	const char* _pTt, 
	auto _lvl) const
{
	auto snake = std::make_shared<Snake::SnakeBody>(_pTh, _pTt);

	snake->SetPos(sf::Vector2u(
		_lvl->GetConfigs().startPosX,
		_lvl->GetConfigs().startPosY));

	return snake;
}

std::shared_ptr<GraphicField::GraphicField> App::createGrapcfhicField(auto _lvl) const
{
	auto gf = std::make_shared<GraphicField::GraphicField>(_lvl);

	return gf;
}

std::shared_ptr<Apple> App::createApple(const char* _pTa, auto _lvl) const
{
	auto apple = std::make_shared<Apple>(_pTa);
	
	return apple;
}

void App::setCurMode(Hud::MODE _mode)
{
	std::lock_guard<std::mutex> lk(defMt);

	currentMode = _mode;
}


