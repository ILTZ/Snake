#include "BaseDrawable.h"

using namespace BDraw;

BaseDrawableCircle::BaseDrawableCircle(const char* _pathToTexture, float _radius)
{
	baseTexture = new sf::Texture();
	baseTexture->loadFromFile(_pathToTexture);

	baseFigure = new sf::CircleShape(_radius);
	baseFigure->setOrigin(_radius, _radius);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
}

BaseDrawableCircle::BaseDrawableCircle(const BaseDrawableCircle& _other)
{
	baseTexture = new sf::Texture(*_other.baseTexture);

	auto _rad = _other.baseFigure->getRadius();
	baseFigure = new sf::CircleShape(_rad);
	baseFigure->setOrigin(_rad, _rad);
	baseFigure->setRotation(0);
	baseFigure->setTexture(&*baseTexture);
}

BDraw::BaseDrawableCircle::~BaseDrawableCircle()
{
}

void BaseDrawableCircle::SetPos(const sf::Vector2f& _newPos)
{
	changeRotation(_newPos);
	curPos = _newPos;
}

const sf::Vector2f& BDraw::BaseDrawableCircle::GetPos() const
{
	return curPos;
}

void BDraw::BaseDrawableCircle::Draw(sf::RenderWindow& _wnd)
{
	baseFigure->setPosition(sf::Vector2f(
		curPos.x * (float)baseTexture->getSize().x - baseFigure->getOrigin().x,
		curPos.y * (float)baseTexture->getSize().y - baseFigure->getOrigin().y)
		);
	_wnd.draw(*baseFigure);
}

void BDraw::BaseDrawableCircle::changeRotation(const sf::Vector2f& _newPos)
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
