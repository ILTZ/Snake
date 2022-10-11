#include "DrawableCircle.h"

DrawableCircle::DrawableCircle(const char* _pathToTexture)
{
	baseTexture = new sf::Texture();
	baseTexture->loadFromFile(_pathToTexture);

	currentSize.x = static_cast<float>(baseTexture->getSize().x);
	currentSize.y = static_cast<float>(baseTexture->getSize().y);

	baseFigure = new sf::CircleShape(currentSize.x / 2.f);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(currentSize.x / 2.f, currentSize.y / 2.f);

}

DrawableCircle::DrawableCircle(const DrawableCircle& _other)
{
	baseTexture = new sf::Texture(*_other.baseTexture);

	currentSize.x = static_cast<float>(baseTexture->getSize().x);
	currentSize.y = static_cast<float>(baseTexture->getSize().y);

	baseFigure = new sf::CircleShape(_other.baseFigure->getRadius());
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(currentSize.x / 2.f, currentSize.y / 2.f);

	currentPosition = _other.currentPosition;

}

DrawableCircle& DrawableCircle::operator=(const DrawableCircle& _other)
{
	baseFigure.Reset();
	baseTexture.Reset();

	baseTexture = new sf::Texture(*_other.baseTexture);

	currentSize.x = static_cast<float>(baseTexture->getSize().x);
	currentSize.y = static_cast<float>(baseTexture->getSize().y);

	baseFigure = new sf::CircleShape(_other.baseFigure->getRadius());
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(currentSize.x / 2.f, currentSize.y / 2.f);

	currentPosition = _other.currentPosition;

	return *this;
}

DrawableCircle::DrawableCircle(DrawableCircle&& _other) noexcept
{
	if (this != &_other)
	{
		baseTexture = _other.baseTexture.Release();
		baseFigure = _other.baseFigure.Release();

		currentPosition = _other.currentPosition;

		currentSize = _other.currentSize;
	}
}

DrawableCircle::~DrawableCircle()
{
}

void DrawableCircle::SetPosition(const sf::Vector2f& _newPos)
{
	baseFigure->setPosition(_newPos);
	changeRotation(_newPos);

	currentPosition = _newPos;
}

void DrawableCircle::SetScale(const sf::Vector2f& _newScale)
{
	width *= _newScale.x;
	height *= _newScale.y;

	currentSize.x *= _newScale.x;
	currentSize.y *= _newScale.y;

	currentScale = _newScale;

	baseFigure->setRadius(baseFigure->getRadius() * _newScale.x);
	baseFigure->setOrigin(baseFigure->getRadius(), baseFigure->getRadius());
}

void DrawableCircle::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(*baseFigure);
}

const sf::Vector2f DrawableCircle::GetSize() const
{
	return currentSize;
}

const sf::Vector2f DrawableCircle::calculateCurrentWindowPos(const sf::Vector2u& _fieldPos) const
{
	return sf::Vector2f(
		static_cast<float>(_fieldPos.x) * currentSize.x + baseFigure->getRadius(),
		static_cast<float>(_fieldPos.y) * currentSize.y + currentSize.y / 2.f);
}

void DrawableCircle::changeRotation(const sf::Vector2f& _newPos)
{
	if (_newPos.y > currentPosition.y)		//Down
	{
		baseFigure->setRotation(180.f);
	}
	else if (_newPos.y < currentPosition.y)	//Up
	{
		baseFigure->setRotation(0.f);
	}
	else if (_newPos.x > currentPosition.x) //Left
	{
		baseFigure->setRotation(90.f);
	}
	else if (_newPos.x < currentPosition.x)	//Right
	{
		baseFigure->setRotation(270.f);
	}
}
