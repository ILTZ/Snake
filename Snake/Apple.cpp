#include "Apple.h"

Apple::Apple(const char* _pathToText) : BaseDrawable(_pathToText)
{

}

void Apple::Draw(sf::RenderWindow& _wnd)
{
	BaseDrawable::Draw(_wnd);
}

void Apple::SetPos(const sf::Vector2u& _pos)
{
	BaseDrawable::SetPos(_pos);
}
