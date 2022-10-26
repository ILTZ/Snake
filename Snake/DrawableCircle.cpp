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

	currentScale = { 1.f,1.f };
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

	currentScale = { 1.f,1.f };
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

	currentPosition		= _other.currentPosition;
	currentScale		= _other.currentScale;

	return *this;
}

DrawableCircle::DrawableCircle(DrawableCircle&& _other) noexcept
{
	if (this != &_other)
	{
		baseTexture = _other.baseTexture.Release();
		baseFigure = _other.baseFigure.Release();

		currentPosition		= _other.currentPosition;
		currentScale		= _other.currentScale;
		currentSize			= _other.currentSize;
	}
}

DrawableCircle::~DrawableCircle()
{
}

const sf::Vector2f DrawableCircle::GetPosition() const
{
	return baseFigure->getPosition();
}

void DrawableCircle::SetPosition(const sf::Vector2f& _newPos)
{
	baseFigure->setPosition(_newPos);

	if (autoRotation)
		changeRotation(_newPos);

	currentPosition = _newPos;
}

const sf::Vector2f DrawableCircle::GetScale() const
{
	return currentScale;
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

void DrawableCircle::Draw(sf::RenderWindow& _target)
{
	_target.draw(*baseFigure);
}

void DrawableCircle::SetCurrentRotation(ROTATING_BASE::Rotation _rot)
{
	if (currentRotation == _rot)
		return;

	currentRotation = _rot;

	switch (_rot)
	{
	case ROTATING_BASE::Rotation::G_0:
		baseFigure->setRotation(0.f);
		break;

	case ROTATING_BASE::Rotation::G_90:
		baseFigure->setRotation(90.f);
		break;

	case ROTATING_BASE::Rotation::G_180:
		baseFigure->setRotation(180.f);
		break;

	case ROTATING_BASE::Rotation::G_270:
		baseFigure->setRotation(270.f);
		break;

	default:
		break;
	}
}

const ROTATING_BASE::Rotation DrawableCircle::GetCurrentRotation() const
{
	return currentRotation;
}

const sf::Vector2f DrawableCircle::GetSize() const
{
	return currentSize;
}

void DrawableCircle::SetSize(const sf::Vector2f _newSize)
{
	currentSize = _newSize;

	baseFigure->setRadius(currentSize.x / 2.f);
	baseFigure->setOrigin(baseFigure->getRadius(), baseFigure->getRadius());
}

const sf::Vector2f DrawableCircle::calculateCurrentWindowPos(const sf::Vector2i& _fieldPos) const
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
