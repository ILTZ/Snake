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

	public:
		BaseDrawableCircle(const char* _pathToTexture, float _radius = 20.f);
		BaseDrawableCircle(const BaseDrawableCircle& _other);
		~BaseDrawableCircle();

	public:
		void SetPos(const sf::Vector2f& _newPos);
		void Draw(sf::RenderWindow& _wnd);
	
	private:
		void changeRotation(const sf::Vector2f& _newPos);
	};

}

#endif

