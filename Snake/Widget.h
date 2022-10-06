#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "SmartPointer.h"
#include "BaseText.h"

class BaseWidget
{
protected:
	SmartPointer::SmartPointer<sf::Texture>			mainTexture;
	SmartPointer::SmartPointer<sf::RectangleShape>	rectangleShape;

public:
	BaseWidget(const char* _pathToText);
	BaseWidget(const BaseWidget& _other);
	BaseWidget(BaseWidget&& _other)				noexcept;

	virtual ~BaseWidget();

public:
	BaseWidget& operator=(const BaseWidget&)	= delete;

public:
	virtual void Draw(sf::RenderWindow& _target)				= 0;
	virtual void SetScale(const sf::Vector2f& _newScale)		= 0;
	virtual void SetPosition(const sf::Vector2f& _newPosition)	= 0;

};



#endif // !WIDGET_H





