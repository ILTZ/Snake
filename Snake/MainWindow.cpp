#include "MainWindow.h"
#include "ScaleDeterminant.h"

#include <SFML/Graphics/Image.hpp>

using namespace MainWin;

MainWin::MainWindow::MainWindow(
	CLoader::Loader* _loder, 
	const std::string& _title, 
	int32_t _style, 
	const sf::ContextSettings& _settings)
{
	auto wndConf = _loder->GetWndConfigs();

	wWidth		= wndConf.width;
	wHeight		= wndConf.height;
	pathToFont	= wndConf.pathToFont;

	background = new Background(wndConf.pathToBackgound, wWidth, wHeight);

	wnd.create(sf::VideoMode(wWidth, wHeight), wndConf.title, _style, _settings);
	
	sf::Image icon;
	icon.loadFromFile(wndConf.pathToIcon);
	wnd.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}


void MainWin::MainWindow::Draw(BaseDrawable& _whatDraw)
{
	_whatDraw.Draw(wnd);
}
void MainWin::MainWindow::DrawUI(const APP_STATE::AppState& _curState)
{
	if (wnd.isOpen())
	{
		if (_curState.CheckMainMenuState())
			background->Draw(wnd);


		hud->DrawUI(wnd, _curState.GetState());
	}
}
void MainWin::MainWindow::DrawLoadingScreen()
{
	BaseText lText(
		pathToFont.c_str(), 
		"Loading...", 
		wHeight / 10u, 
		sf::Color::White, 
		sf::Text::Italic);

	lText.SetPos(sf::Vector2f(
		static_cast<float>(wnd.getSize().x / 2u),
		static_cast<float>(wnd.getSize().y / 2u)));

	wnd.clear();
	lText.Draw(wnd);
	wnd.display();
}


const sf::Vector2u MainWin::MainWindow::GetHudTargetSize() const
{
	return sf::Vector2u(
		static_cast<unsigned int>(static_cast<float>(wWidth) * hudPart),
		wHeight
	);
}
const sf::Vector2u MainWin::MainWindow::GetGameFieldTargetSize() const
{
	return sf::Vector2u(
		static_cast<unsigned int>(static_cast<float>(wWidth) * gameFieldPart),
		wHeight
	);
}

sf::RenderWindow& MainWindow::get()
{
	return wnd;
}
void MainWin::MainWindow::SetHud(std::shared_ptr<UI::Ui> _hud)
{
	hud = _hud;
	// Last quarter of the window
	hud->SetHudSpritePosition(sf::Vector2f(
		static_cast<float>(wnd.getSize().x) * (1.f - hudPart), 0.f));
}
UI::Ui& MainWin::MainWindow::GetUI()
{
	return *hud;
}

#pragma region Events

bool MainWindow::PollEvents()
{
	sf::Event ev;
	while (wnd.pollEvent(ev))
	{
		// Exit game
		if (ev.type == sf::Event::Closed)
			return false;


		switch (ev.type)
		{
		case sf::Event::MouseButtonPressed:
			mouse.AddPressEvent(ev);
			break;

		case sf::Event::MouseButtonReleased:
			mouse.AddReleaseEvent(ev);
			break;

		case sf::Event::KeyReleased:
			kb.AddReleaseEvent(ev);
			break;

		case sf::Event::KeyPressed:
			kb.AddPressEvent(ev);
			break;

		case sf::Event::TextEntered:
			kb.AddCharEvent(ev);
			break;
		}

	}
	return true;
}

std::optional<Keyboard::KeyEvent> MainWin::MainWindow::GetKeyboardEvent()
{
	return kb.GetEvent();
}
std::optional<Keyboard::TextEvent> MainWin::MainWindow::GetTextEvent()
{
	return kb.GetCharEvent();
}
std::optional<MS::MouseEvent> MainWin::MainWindow::GetMouseEvent()
{
	return mouse.GetEvent();
}

#pragma endregion

MainWin::MainWindow::Background::Background(
	const std::string& _pathToTexture, 
	unsigned int _width, 
	unsigned int _height)
{
	bText.loadFromFile(_pathToTexture);
	bSprite.setTexture(bText);

	ScaleDeterminant det;

	auto scale = det.CalculateAbsoluteScale(
		sf::Vector2u(
		static_cast<unsigned int>(bSprite.getGlobalBounds().width),
		static_cast<unsigned int>(bSprite.getGlobalBounds().height)),

		sf::Vector2u(_width, _height));

	bSprite.setScale(scale);
}

void MainWin::MainWindow::Background::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(bSprite);
}
