#include "BaseDrawable.h"


BaseDrawable::BaseDrawableCircle::BaseDrawableCircle(const char* _pathToTexture, float _radius)
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

BaseDrawable::BaseDrawableCircle::BaseDrawableCircle(const BaseDrawableCircle& _other)
{
	baseTexture = new sf::Texture(*_other.baseTexture);

	width = static_cast<float>(baseTexture->getSize().x);
	height = static_cast<float>(baseTexture->getSize().y);

	auto _rad = _other.baseFigure->getRadius();
	baseFigure = new sf::CircleShape(_rad);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(width / 2.f, height / 2.f);

	curPos = _other.curPos;
}

BaseDrawable::BaseDrawableCircle& BaseDrawable::BaseDrawableCircle::operator=(const BaseDrawableCircle& _other)
{
	baseTexture = new sf::Texture(*_other.baseTexture);

	width = static_cast<float>(baseTexture->getSize().x);
	height = static_cast<float>(baseTexture->getSize().y);

	auto _rad = _other.baseFigure->getRadius();
	baseFigure = new sf::CircleShape(_rad);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
	baseFigure->setOrigin(width / 2.f, height / 2.f);

	curPos = _other.curPos;

	return *this;
}

BaseDrawable::BaseDrawableCircle::BaseDrawableCircle(BaseDrawableCircle&& _other) noexcept
{
	if (this != &_other)
	{
		baseTexture = _other.baseTexture.Release();
		baseFigure = _other.baseFigure.Release();

		curPos = _other.curPos;

		width = _other.width;
		height = _other.height;
	}
}

BaseDrawable::BaseDrawableCircle::~BaseDrawableCircle()
{
}

void BaseDrawable::BaseDrawableCircle::SetPos(const sf::Vector2u& _newPos)
{
	changeRotation(_newPos);
	curPos = _newPos;
}

const sf::Vector2u& BaseDrawable::BaseDrawableCircle::GetPos() const
{
	return curPos;
}

void BaseDrawable::BaseDrawableCircle::Draw(sf::RenderWindow& _wnd)
{
	baseFigure->setPosition(sf::Vector2f(
		static_cast<float>(curPos.x) * (baseFigure->getRadius() * 2.f) + baseFigure->getOrigin().x,
		static_cast<float>(curPos.y) * (baseFigure->getRadius() * 2.f) + baseFigure->getOrigin().y));

	_wnd.draw(*baseFigure);
}

void BaseDrawable::BaseDrawableCircle::SetScale(const sf::Vector2f& _newScale)
{
	baseFigure->setScale(_newScale);
}

void BaseDrawable::BaseDrawableCircle::SetNewSize(const sf::Vector2f& _newSize)
{
	width	= _newSize.x;
	height	= _newSize.y;
}

const sf::Vector2f BaseDrawable::BaseDrawableCircle::GetSize() const
{
	return sf::Vector2f(width, height);
}

void BaseDrawable::BaseDrawableCircle::changeRotation(const sf::Vector2u& _newPos)
{
	if (_newPos.y > curPos.y)
	{
		baseFigure->setRotation(180.f);
	}
	else if (_newPos.y < curPos.y)
	{
		baseFigure->setRotation(0.f);
	}
	else if (_newPos.x > curPos.x)
	{
		baseFigure->setRotation(90.f);
	}
	else if (_newPos.x < curPos.x)
	{
		baseFigure->setRotation(270.f);
	}
}
