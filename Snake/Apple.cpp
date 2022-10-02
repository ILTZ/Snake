#include "Apple.h"

Apple::Apple(const char* _pathToText) : BaseDrawableCircle(_pathToText)
{

}

void Apple::Draw(sf::RenderWindow& _wnd)
{
	BaseDrawableCircle::Draw(_wnd);
}

void Apple::SetScale(const sf::Vector2f& _newScale)
{
	BaseDrawableCircle::SetSpriteScale(_newScale);
}

void Apple::SetPos(const sf::Vector2u& _pos)
{
	BaseDrawableCircle::SetPos(_pos);
}
