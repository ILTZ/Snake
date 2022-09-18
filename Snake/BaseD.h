#ifndef BASED_H
#define BASED_H

#include "SFML/Graphics/RenderWindow.hpp"

class BaseD
{
public:
	virtual void Draw(sf::RenderWindow& _wnd)				= 0;
	virtual void SetSpriteScale(int _width, int _height)	= 0;

	virtual ~BaseD()
	{};
};




#endif
