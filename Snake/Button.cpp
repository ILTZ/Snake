#include "Button.h"
#include <iostream>

#define LOG(str) {std::cout << str << std::endl;}

using namespace Buttons;

Button::Button(Btn _wBtn, const char* _pathToU, const char* _pathToD, const char* _pathToFont, const char* _btnText) :
	whatBtn{ _wBtn }, curMode{BtnMode::RELEASED}
{
	btns[BtnMode::RELEASED] = BtnConf(_pathToU);
	btns[BtnMode::PRESSED] = BtnConf(_pathToD);

	btns[BtnMode::PRESSED].rectShape->setOrigin(btns[BtnMode::RELEASED].rectShape->getOrigin().x, 
		btns[BtnMode::RELEASED].rectShape->getOrigin().y + 
		getBtnSizeDif(*btns[BtnMode::RELEASED].rectShape, *btns[BtnMode::PRESSED].rectShape).y);


	if (_btnText)
		text = new TextConf(_pathToFont, _btnText);
	else
		text = new TextConf(_pathToFont, "NONE");

}

Buttons::Button::~Button()
{

#ifndef NDEBUG
	LOG("DEstr btn");
#endif
}

void Buttons::Button::SwitchCurrentState(BtnMode _mode)
{
	curMode = _mode;
}

void Buttons::Button::Rescale(const sf::Vector2f& _newScale)
{
	btns[BtnMode::PRESSED].rectShape->setScale(_newScale);
	btns[BtnMode::RELEASED].rectShape->setScale(_newScale);

	text->btnText.setScale(_newScale);
}

void Buttons::Button::Draw(sf::RenderWindow& _wnd, const sf::Vector2f& _pos)
{
	auto nPosY = _pos.y;
	auto tDif = 0.f;
	auto dif	= getBtnSizeDif(*btns[BtnMode::RELEASED].rectShape, 
		*btns[BtnMode::PRESSED].rectShape).y;

	if (curMode == BtnMode::PRESSED)
	{
		nPosY	+= dif;
		tDif	-= dif;
	}
	else
	{
		nPosY -= dif;
	}

	btns[curMode].rectShape->setPosition(_pos.x, nPosY);
	text->btnText.setPosition(btns[curMode].rectShape->getPosition().x,
		btns[curMode].rectShape->getPosition().y + tDif);
	

	_wnd.draw(*btns[curMode].rectShape);
	_wnd.draw(text->btnText);
}

Btn Buttons::Button::GetBtnDest() const
{
	return whatBtn;
}

BtnMode Buttons::Button::GetBtnMode() const
{
	return curMode;
}

bool Buttons::Button::GetTouch(float _x, float _y)
{
	auto& btn = btns[curMode].rectShape;
	if (_x >= (btn->getPosition().x - (btn->getSize().x / 2.f)) &&
		_x <= (btn->getPosition().x + (btn->getSize().x / 2.f)) &&
		_y >= (btn->getPosition().y - (btn->getSize().y / 2.f)) &&
		_y <= (btn->getPosition().y + (btn->getSize().y / 2.f))
		)
	{
		if (curMode == BtnMode::PRESSED)
			curMode = BtnMode::RELEASED;
		else
			curMode = BtnMode::PRESSED;

		return true;
	}

	return false;
}

sf::Vector2f Buttons::Button::getBtnSizeDif(const sf::RectangleShape& _first, const sf::RectangleShape& _second)
{
	return 
		sf::Vector2f(
		_first.getSize().x - _second.getSize().x,
		_first.getSize().y - _second.getSize().y
	);
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

Buttons::Button::TextConf::TextConf(const char* _pathToFont, const std::string& _text) 
{
	textFont.loadFromFile(_pathToFont);

	btnText.setString(_text);
	btnText.setFont(textFont);
	btnText.setCharacterSize(25);
	btnText.setFillColor(sf::Color::Black);
	btnText.setStyle(sf::Text::Italic);

	btnText.setOrigin(
		btnText.getGlobalBounds().width / 2.f,
		btnText.getGlobalBounds().height);

}

Btn Buttons::operator++(Btn& _x)
{
	return _x = static_cast<Btn>(std::underlying_type<Btn>::type(_x) + 1);
}
