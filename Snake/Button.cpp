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

void Buttons::Button::SetState(BtnState _mode)
{
	curState = _mode;
	calculateAndSetBtnsShift();
}

void Buttons::Button::SetScale(const sf::Vector2f& _newScale)
{
	btns[BtnState::PRESSED].rectShape->setScale(_newScale);
	btns[BtnState::RELEASED].rectShape->setScale(_newScale);

	for (auto& el : btns)
	{
		el.second.width		*= _newScale.x;
		el.second.height	*= _newScale.y;
	}

	text->SetScale(_newScale);
}

void Buttons::Button::SetPosition(const sf::Vector2f& _newPosition)
{
	btnPosition = _newPosition;
	calculateAndSetBtnsShift();
}

void Buttons::Button::Draw(sf::RenderWindow& _wnd)
{
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
	auto& btn = btns[curState];
	if (_x >= (btns[curState].rectShape->getPosition().x - (btns[curState].width / 2.f)) &&
		_x <= (btns[curState].rectShape->getPosition().x + (btns[curState].width / 2.f)) &&
		_y >= (btns[curState].rectShape->getPosition().y - (btns[curState].height / 2.f)) &&
		_y <= (btns[curState].rectShape->getPosition().y + (btns[curState].height / 2.f))
		)
	{
		if (curState == BtnState::PRESSED)
			SetState(BtnState::RELEASED);
		else
			SetState(BtnState::PRESSED);

		return true;
	}

	return false;
}

void Buttons::Button::calculateAndSetBtnsShift()
{
	auto nPosY = btnPosition.y;
	auto tDif = 0.f;

	if (curState == BtnState::PRESSED)
	{
		nPosY += btnsSizeDifference.y;
		tDif -= btnsSizeDifference.y;
	}
	else
	{
		nPosY -= btnsSizeDifference.y;
	}

	btns[curState].rectShape->setPosition(btnPosition.x, nPosY);
	text->SetPos(sf::Vector2f(
		btns[curState].rectShape->getPosition().x,
		btns[curState].rectShape->getPosition().y + tDif));
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

	width	= rectShape->getSize().x;
	height	= rectShape->getSize().y;
}

BtnPurpose Buttons::operator++(BtnPurpose& _x)
{
	return _x = static_cast<BtnPurpose>(std::underlying_type<BtnPurpose>::type(_x) + 1);
}
