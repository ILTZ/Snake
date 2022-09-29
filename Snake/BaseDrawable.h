#ifndef BDRAW_H
#define BDRAW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>


#include "SmartPointer.h"

namespace BaseDrawable
{
	class BaseDrawable
	{
	protected:
		SmartPointer::SmartPointer<sf::CircleShape>	baseFigure;
		SmartPointer::SmartPointer<sf::Texture>		baseTexture;

		sf::Vector2u curPos;

		float width = 0.f;
		float height = 0.f;

	public:
		BaseDrawable(const char* _pathToTexture, float _radius = 20.f);
		BaseDrawable(const BaseDrawable& _other);
		BaseDrawable& operator=(const BaseDrawable& _other);
		BaseDrawable(BaseDrawable&& _other) noexcept;
		virtual ~BaseDrawable();

	public:
		void SetPos(const sf::Vector2u& _newPos);
		const sf::Vector2u& GetPos() const;
		void Draw(sf::RenderWindow& _wnd);
		void SetSpriteScale(const sf::Vector2f& _newScale);
		void SetNewSize(const sf::Vector2f& _newSize);
		const sf::Vector2f GetSize() const;

	private:
		void changeRotation(const sf::Vector2u& _newPos);
	};

};

#endif

