#include "DrawableCircle.h"

DrawableCircle::DrawableCircle(const char* _pathToTexture, float _radius)
{
	baseTexture = new sf::Texture();
	baseTexture->loadFromFile(_pathToTexture);

	width = static_cast<float>(baseTexture->getSize().x);
	height = static_cast<float>(baseTexture->getSize().y);

	baseFigure = new sf::CircleShape(width / 2.f);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(width / 2.f, height / 2.f);
}

DrawableCircle::DrawableCircle(const DrawableCircle& _other)
{
	baseTexture = new sf::Texture(*_other.baseTexture);

	width = static_cast<float>(baseTexture->getSize().x);
	height = static_cast<float>(baseTexture->getSize().y);

	auto _rad = _other.baseFigure->getRadius();
	baseFigure = new sf::CircleShape(_rad);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(width / 2.f, height / 2.f);

	currentPosition = _other.currentPosition;
}

DrawableCircle& DrawableCircle::operator=(const DrawableCircle& _other)
{
	baseTexture = new sf::Texture(*_other.baseTexture);

	width = static_cast<float>(baseTexture->getSize().x);
	height = static_cast<float>(baseTexture->getSize().y);

	auto _rad = _other.baseFigure->getRadius();
	baseFigure = new sf::CircleShape(_rad);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(width / 2.f, height / 2.f);

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

		width = _other.width;
		height = _other.height;
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
	return sf::Vector2f(width, height);
}

const sf::Vector2f DrawableCircle::calculateCurrentWindowPos(const sf::Vector2u& _fieldPos) const
{
	return sf::Vector2f(
		static_cast<float>(_fieldPos.x) * width + baseFigure->getRadius(),
		static_cast<float>(_fieldPos.y) * height + height / 2.f);
}

void DrawableCircle::changeRotation(const sf::Vector2f& _newPos)
{
	if (_newPos.y > currentPosition.y)
	{
		baseFigure->setRotation(180.f);
	}
	else if (_newPos.y < currentPosition.y)
	{
		baseFigure->setRotation(0.f);
	}
	else if (_newPos.x > currentPosition.x)
	{
		baseFigure->setRotation(90.f);
	}
	else if (_newPos.x < currentPosition.x)
	{
		baseFigure->setRotation(270.f);
	}
}
