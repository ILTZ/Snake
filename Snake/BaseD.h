#ifndef BASED_H
#define BASED_H

#include "SFML/Graphics/RenderWindow.hpp"

class BaseD
{
public:
	virtual void Draw(sf::RenderWindow&)		= 0;
	virtual void SetPos(const sf::Vector2u&)	= 0;

	virtual void SetScale(const sf::Vector2f&)	= 0;

	virtual ~BaseD()
	{};
};




#endif
