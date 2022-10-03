#include "Button.h"
#include <iostream>

#define LOG(str) {std::cout << str << std::endl;}

using namespace Buttons;

Button::Button(
	BtnPurpose _btnPurpose,
	const char* _pathToRelesedBtnTexture,
	const char* _pathToPressedBtnTexture,
	const char* _pathToFont, 
	const char* _btnText) :
	whatBtn{ _btnPurpose }, 
	curMode{BtnState::RELEASED}
{
	btns[BtnState::RELEASED] = BtnConf(_pathToRelesedBtnTexture);
	btns[BtnState::PRESSED] = BtnConf(_pathToPressedBtnTexture);

	btnsSizeDifference.x = btns[BtnState::RELEASED].rectShape->getSize().x - btns[BtnState::PRESSED].rectShape->getSize().x;
	btnsSizeDifference.y = btns[BtnState::RELEASED].rectShape->getSize().y - btns[BtnState::PRESSED].rectShape->getSize().y;

	btns[BtnState::PRESSED].rectShape->setOrigin(
		btns[BtnState::RELEASED].rectShape->getOrigin().x,
		btns[BtnState::RELEASED].rectShape->getOrigin().y + btnsSizeDifference.y);

	text = new TextConf(_pathToFont, _btnText);

}

Buttons::Button::~Button()
{

#ifndef NDEBUG
	LOG("DEstr btn");
#endif
}

void Buttons::Button::SwitchCurrentState(BtnState _mode)
{
	curMode = _mode;
}

void Buttons::Button::Rescale(const sf::Vector2f& _newScale)
{
	btns[BtnState::PRESSED].rectShape->setScale(_newScale);
	btns[BtnState::RELEASED].rectShape->setScale(_newScale);

	text->btnText.setScale(_newScale);
}

void Buttons::Button::Draw(sf::RenderWindow& _wnd, const sf::Vector2f& _pos)
{
	auto nPosY = _pos.y;
	auto tDif = 0.f;

	if (curMode == BtnState::PRESSED)
	{
		nPosY	+= btnsSizeDifference.y;
		tDif	-= btnsSizeDifference.y;
	}
	else
	{
		nPosY -= btnsSizeDifference.y;
	}

	btns[curMode].rectShape->setPosition(_pos.x, nPosY);
	text->btnText.setPosition(
		btns[curMode].rectShape->getPosition().x,
		btns[curMode].rectShape->getPosition().y + tDif);
	

	_wnd.draw(*btns[curMode].rectShape);
	_wnd.draw(text->btnText);
}

BtnPurpose Buttons::Button::GetBtnPurpose() const
{
	return whatBtn;
}

BtnState Buttons::Button::GetBtnState() const
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
		if (curMode == BtnState::PRESSED)
			curMode = BtnState::RELEASED;
		else
			curMode = BtnState::PRESSED;

		return true;
	}

	return false;
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

BtnPurpose Buttons::operator++(BtnPurpose& _x)
{
	return _x = static_cast<BtnPurpose>(std::underlying_type<BtnPurpose>::type(_x) + 1);
}
