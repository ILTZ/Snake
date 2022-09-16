#ifndef BDRAW_H
#define BDRAW_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "BaseD.h"
#include "SmartPointer.h"

namespace BDraw
{
	class BaseDrawableCircle : public BaseD
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
		const sf::Vector2f& GetPos() const;
		virtual void Draw(sf::RenderWindow& _wnd) override;
	
	private:
		void changeRotation(const sf::Vector2f& _newPos);
	};

}

#endif

