#ifndef DRAWABLE_RECTANGLE_H
#define DRAWABLE_RECTANGLE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "SmartPointer.h"
#include "BaseDrawable.h"

// Base Drawable Rectangle

class DrawableRectangle : public BaseDrawable
{
protected:
	SmartPointer::SmartPointer<sf::Texture>			mainTexture;
	SmartPointer::SmartPointer<sf::RectangleShape>	rectangleShape;

public:
	DrawableRectangle(const char* _pathToText);
	DrawableRectangle(const DrawableRectangle& _other);
	DrawableRectangle(DrawableRectangle&& _other)				noexcept;

	DrawableRectangle& operator=(const DrawableRectangle& _other);

	virtual ~DrawableRectangle();

public:
	virtual void Draw(sf::RenderWindow& _target)				override;

public:
	virtual const sf::Vector2f GetScale()						const override;
	virtual void SetScale(const sf::Vector2f& _newScale)		override;

	virtual const sf::Vector2f GetPosition()					const override;
	virtual void SetPosition(const sf::Vector2f& _newPosition)	override;

	virtual const sf::Vector2f GetSize()						const override;
	virtual void SetSize(const sf::Vector2f _newSize)			override;

};


#endif // !WIDGET_H





