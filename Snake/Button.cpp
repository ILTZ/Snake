#include "Button.h"

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

	btnsSizeDifference = calcRectShapeSizeDifference(
		*btns[BtnState::RELEASED].rectShape, 
		*btns[BtnState::PRESSED].rectShape);

	btns[BtnState::PRESSED].rectShape->setOrigin(
		btns[BtnState::RELEASED].rectShape->getOrigin().x,
		btns[BtnState::RELEASED].rectShape->getOrigin().y + btnsSizeDifference.y);

	text = new BaseText(
		_pathToFont,
		_btnText,
		static_cast<unsigned int>(btns[BtnState::PRESSED].rectShape->getSize().y / 2.f),
		sf::Color::Black,
		sf::Text::Italic
	);
}

Buttons::Button::~Button()
{

}

void Buttons::Button::SetState(BtnState _mode)
{
	curState = _mode;
	calculateAndSetBtnsShift(currentPosition);
}

void Buttons::Button::SetScale(const sf::Vector2f& _newScale)
{
	currentScale = _newScale;

	for (auto& el : btns)
	{
		el.second.rectShape->setScale(_newScale);
	}

	btnsSizeDifference = calcRectShapeSizeDifference(
		*btns[BtnState::RELEASED].rectShape,
		*btns[BtnState::PRESSED].rectShape);

	text->SetScale(_newScale);
	calculateAndSetBtnsShift(currentPosition);
}

void Buttons::Button::SetPosition(const sf::Vector2f& _newPos)
{
	currentPosition = _newPos;
	calculateAndSetBtnsShift(currentPosition);
}

void Buttons::Button::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(*btns[curState].rectShape);
	text->Draw(_wnd);
}

const sf::Vector2f Buttons::Button::GetSize() const
{
	return sf::Vector2f(
		btns[curState].rectShape->getGlobalBounds().width,
		btns[curState].rectShape->getGlobalBounds().height);
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
	if (_x >= (btns[curState].rectShape->getPosition().x - (btns[curState].rectShape->getGlobalBounds().width / 2.f)) &&
		_x <= (btns[curState].rectShape->getPosition().x + (btns[curState].rectShape->getGlobalBounds().width / 2.f)) &&
		_y >= (btns[curState].rectShape->getPosition().y - (btns[curState].rectShape->getGlobalBounds().height / 2.f)) &&
		_y <= (btns[curState].rectShape->getPosition().y + (btns[curState].rectShape->getGlobalBounds().height / 2.f))
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

void Buttons::Button::calculateAndSetBtnsShift(const sf::Vector2f& _btnPos)
{
	auto nPosY = _btnPos.y;
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

	btns[curState].rectShape->setPosition(_btnPos.x, nPosY);
	text->SetPos(sf::Vector2f(
		btns[curState].rectShape->getPosition().x,
		btns[curState].rectShape->getPosition().y + tDif));
}

const sf::Vector2f Buttons::Button::calcRectShapeSizeDifference(const sf::RectangleShape& _first, const sf::RectangleShape& _second) const
{
	return sf::Vector2f(
		_first.getGlobalBounds().width - _second.getGlobalBounds().width,
		_first.getGlobalBounds().height - _second.getGlobalBounds().height
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

BtnPurpose Buttons::operator++(BtnPurpose& _x)
{
	return _x = static_cast<BtnPurpose>(std::underlying_type<BtnPurpose>::type(_x) + 1);
}
