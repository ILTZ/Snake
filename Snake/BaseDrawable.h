#ifndef BDRAW_H
#define BDRAW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>


#include "SmartPointer.h"

namespace BDraw
{
	class BaseDrawableCircle
	{
	protected:
		SmartPointer::SmartPointer<sf::CircleShape>	baseFigure;
		SmartPointer::SmartPointer<sf::Texture>		baseTexture;

		sf::Vector2f curPos;

		float width		= 0.f;
		float height	= 0.f;

	public:
		BaseDrawableCircle(const char* _pathToTexture, float _radius = 20.f);
		BaseDrawableCircle(const BaseDrawableCircle& _other);
		~BaseDrawableCircle();

	public:
		void SetPos(const sf::Vector2f& _newPos);
		const sf::Vector2f& GetPos() const;
		void Draw(sf::RenderWindow& _wnd);
		void SetSpriteScale(const sf::Vector2f& _newScale);
		void SetNewSize(const sf::Vector2f& _newSize);
		const sf::Vector2f GetSize() const;

	private:
		void changeRotation(const sf::Vector2f& _newPos);
	};

}

#endif

