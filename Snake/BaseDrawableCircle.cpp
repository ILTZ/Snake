#include "BaseDrawableCircle.h"

BDC::BaseDrawableCircle::BaseDrawableCircle(const char* _pathToTexture, float _radius)
{
	baseTexture = new sf::Texture();
	baseTexture->loadFromFile(_pathToTexture);

	width	= static_cast<float>(baseTexture->getSize().x);
	height	= static_cast<float>(baseTexture->getSize().y);

	baseFigure = new sf::CircleShape(width / 2.f);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(width / 2.f, height / 2.f);
}

BDC::BaseDrawableCircle::BaseDrawableCircle(const BaseDrawableCircle& _other)
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

BDC::BaseDrawableCircle& BDC::BaseDrawableCircle::operator=(const BaseDrawableCircle& _other)
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

BDC::BaseDrawableCircle::BaseDrawableCircle(BaseDrawableCircle&& _other) noexcept
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

BDC::BaseDrawableCircle::~BaseDrawableCircle()
{
}

void BDC::BaseDrawableCircle::SetPos(const sf::Vector2u& _newPos)
{
	changeRotation(_newPos);
	currentPosition = _newPos;

	baseFigure->setPosition(sf::Vector2f(
		static_cast<float>(currentPosition.x) * width + baseFigure->getRadius(),
		static_cast<float>(currentPosition.y) * height + height / 2.f));
}

const sf::Vector2u& BDC::BaseDrawableCircle::GetPos() const
{
	return currentPosition;
}

void BDC::BaseDrawableCircle::Draw(sf::RenderWindow& _wnd)
{
	

	_wnd.draw(*baseFigure);
}

void BDC::BaseDrawableCircle::SetScale(const sf::Vector2f& _newScale)
{
	width	*= _newScale.x;
	height	*= _newScale.y;

	currentScale = _newScale;

	baseFigure->setRadius(baseFigure->getRadius() * _newScale.x);
	baseFigure->setOrigin(baseFigure->getRadius(), baseFigure->getRadius());

	baseFigure->setPosition(sf::Vector2f(
		static_cast<float>(currentPosition.x) * width + baseFigure->getRadius(),
		static_cast<float>(currentPosition.y) * height + height / 2.f));
}

const sf::Vector2f BDC::BaseDrawableCircle::GetScale() const
{
	return currentScale;
}

const sf::Vector2f BDC::BaseDrawableCircle::GetSize() const
{
	return sf::Vector2f(width, height);
}

void BDC::BaseDrawableCircle::changeRotation(const sf::Vector2u& _newPos)
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
