#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "SmartPointer.h"
#include "BaseD.h"


class BaseWidget : public BaseD
{
protected:
	SmartPointer::SmartPointer<sf::Texture>			mainTexture;
	SmartPointer::SmartPointer<sf::RectangleShape>	rectangleShape;

public:
	BaseWidget(const char* _pathToText);
	BaseWidget(const BaseWidget& _other);
	BaseWidget(BaseWidget&& _other)				noexcept;

public:
	BaseWidget& operator=(const BaseWidget&)	= delete;

public:
	virtual void Draw(sf::RenderWindow& _wnd)		= 0;
	virtual void SetPos(const sf::Vector2u& _pos)	= 0;

	virtual void SetSpriteScale(
		unsigned int _width,
		unsigned int _height,
		unsigned int _lwlW,
		unsigned int _lwlH)	= 0;


};



#endif // !WIDGET_H





