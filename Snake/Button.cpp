#include "Button.h"

using namespace Buttons;

Button::Button(const char* _pathToU, const char* _pathToD, const char* _pathToText, const char* _btnText) :
	curMode{BtnMode::NONE}
{
	btns[BtnMode::PRESSED]	= BtnConf(_pathToD);
	btns[BtnMode::RELEASED] = BtnConf(_pathToU);

	if (_btnText)
		text = new TextConf(_pathToText, _btnText);
	else
		text = new TextConf(_pathToText, "NONE");
}

void Buttons::Button::SwitchCurrentState(BtnMode _mode)
{
	curMode = _mode;
}

void Buttons::Button::Rescale(const sf::Vector2f& _newScale)
{
	btns[BtnMode::PRESSED].rectShape->setScale(_newScale);
	btns[BtnMode::RELEASED].rectShape->setScale(_newScale);

	text->btnText->setScale(_newScale);
}

void Buttons::Button::Draw(sf::RenderWindow& _wnd, const sf::Vector2f& _pos)
{
	text->btnText->setPosition(_pos);
	btns[curMode].rectShape->setPosition(_pos);

	_wnd.draw(*btns[curMode].rectShape);
	_wnd.draw(*text->btnText);
}

Buttons::Button::BtnConf::BtnConf(const char* _pathToBtn) : mainText{new sf::Texture()}
{
	mainText->loadFromFile(_pathToBtn);

	rectShape = new sf::RectangleShape(sf::Vector2f(
		static_cast<float>(mainText->getSize().x), 
		static_cast<float>(mainText->getSize().y)));

	rectShape->setTexture(&*mainText);
	rectShape->setOrigin(static_cast<float>(mainText->getSize().x) / 2.f,
						 static_cast<float>(mainText->getSize().y) / 2.f);
}

Buttons::Button::TextConf::TextConf(const char* _pathToFont, const std::string& _text) : textFont{new sf::Font()}, btnText{new sf::Text()}
{
	textFont->loadFromFile(_pathToFont);

	btnText->setString(_text);
	btnText->setFont(*textFont);
	btnText->setCharacterSize(30);
	btnText->setFillColor(sf::Color::Black);
	btnText->setStyle(sf::Text::Italic);

	btnText->setOrigin(
		btnText->getGlobalBounds().width / 2.f,
		btnText->getGlobalBounds().height / 2.f);
}
