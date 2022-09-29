#ifndef BASED_H
#define BASED_H

#include "SFML/Graphics/RenderWindow.hpp"

class BaseD
{
public:
	virtual void Draw(sf::RenderWindow& _wnd)		= 0;
	virtual void SetPos(const sf::Vector2u& _pos)	= 0;

	virtual void SetSpriteScale(
		unsigned int _width,
		unsigned int _height,
		unsigned int _lwlW,
		unsigned int _lwlH) = 0;

	virtual ~BaseD()
	{};
};




#endif
