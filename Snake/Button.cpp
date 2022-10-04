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
	btnPurpose{ _btnPurpose }, 
	curState{BtnState::RELEASED}
{
	btns[BtnState::RELEASED] = BtnConf(_pathToRelesedBtnTexture);
	btns[BtnState::PRESSED] = BtnConf(_pathToPressedBtnTexture);

	btnsSizeDifference.x = btns[BtnState::RELEASED].rectShape->getSize().x - btns[BtnState::PRESSED].rectShape->getSize().x;
	btnsSizeDifference.y = btns[BtnState::RELEASED].rectShape->getSize().y - btns[BtnState::PRESSED].rectShape->getSize().y;

	btns[BtnState::PRESSED].rectShape->setOrigin(
		btns[BtnState::RELEASED].rectShape->getOrigin().x,
		btns[BtnState::RELEASED].rectShape->getOrigin().y + btnsSizeDifference.y);

	text = new BaseText(
		_pathToFont,
		_btnText,
		25u,
		sf::Color::Black,
		sf::Text::Italic
	);
}

Buttons::Button::~Button()
{

#ifndef NDEBUG
	LOG("DEstr btn");
#endif
}

void Buttons::Button::SwitchCurrentState(BtnState _mode)
{
	curState = _mode;
}

void Buttons::Button::Rescale(const sf::Vector2f& _newScale)
{
	btns[BtnState::PRESSED].rectShape->setScale(_newScale);
	btns[BtnState::RELEASED].rectShape->setScale(_newScale);

	text->SetScale(_newScale);
}

void Buttons::Button::Draw(sf::RenderWindow& _wnd, const sf::Vector2f& _pos)
{
	auto nPosY = _pos.y;
	auto tDif = 0.f;

	if (curState == BtnState::PRESSED)
	{
		nPosY	+= btnsSizeDifference.y;
		tDif	-= btnsSizeDifference.y;
	}
	else
	{
		nPosY -= btnsSizeDifference.y;
	}

	btns[curState].rectShape->setPosition(_pos.x, nPosY);
	text->SetPos(sf::Vector2f(
		btns[curState].rectShape->getPosition().x,
		btns[curState].rectShape->getPosition().y + tDif));
	

	_wnd.draw(*btns[curState].rectShape);
	text->Draw(_wnd);
}

BtnPurpose Buttons::Button::GetBtnPurpose() const
{
	return btnPurpose;
}

BtnState Buttons::Button::GetBtnState() const
{
	return curState;
}

bool Buttons::Button::GetTouch(float _x, float _y)
{
	auto& btn = btns[curState].rectShape;
	if (_x >= (btn->getPosition().x - (btn->getSize().x / 2.f)) &&
		_x <= (btn->getPosition().x + (btn->getSize().x / 2.f)) &&
		_y >= (btn->getPosition().y - (btn->getSize().y / 2.f)) &&
		_y <= (btn->getPosition().y + (btn->getSize().y / 2.f))
		)
	{
		if (curState == BtnState::PRESSED)
			curState = BtnState::RELEASED;
		else
			curState = BtnState::PRESSED;

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

BtnPurpose Buttons::operator++(BtnPurpose& _x)
{
	return _x = static_cast<BtnPurpose>(std::underlying_type<BtnPurpose>::type(_x) + 1);
}
