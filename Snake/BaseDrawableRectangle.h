#ifndef BASE_DRAWABLE_RECTANGLE_H
#define BASE_DRAWABLE_RECTANGLE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "SmartPointer.h"

// Base Drawable Rectangle
namespace BDR
{
	class BaseDrawableRectangle
	{
	protected:
		SmartPointer::SmartPointer<sf::Texture>			mainTexture;
		SmartPointer::SmartPointer<sf::RectangleShape>	rectangleShape;

	public:
		BaseDrawableRectangle(const char* _pathToText);
		BaseDrawableRectangle(const BaseDrawableRectangle& _other);
		BaseDrawableRectangle(BaseDrawableRectangle&& _other)				noexcept;

		virtual ~BaseDrawableRectangle();

	public:
		BaseDrawableRectangle& operator=(const BaseDrawableRectangle&) = delete;

	public:
		virtual void Draw(sf::RenderWindow& _target)				= 0;
		virtual void SetScale(const sf::Vector2f& _newScale)		= 0;
		virtual void SetPosition(const sf::Vector2f& _newPosition)	= 0;

	};
}


#endif // !WIDGET_H





