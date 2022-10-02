#ifndef BDRAW_H
#define BDRAW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>


#include "SmartPointer.h"
#include "BaseD.h"

namespace BaseDrawable
{
	class BaseDrawableCircle : public BaseD
	{
	protected:
		SmartPointer::SmartPointer<sf::CircleShape>	baseFigure;
		SmartPointer::SmartPointer<sf::Texture>		baseTexture;

		sf::Vector2u curPos;

		float width = 0.f;
		float height = 0.f;

	public:
		BaseDrawableCircle(const char* _pathToTexture, float _radius = 20.f);
		BaseDrawableCircle(const BaseDrawableCircle& _other);
		BaseDrawableCircle& operator=(const BaseDrawableCircle& _other);
		BaseDrawableCircle(BaseDrawableCircle&& _other) noexcept;
		virtual ~BaseDrawableCircle();

	public:
		void SetPos(const sf::Vector2u& _newPos)		override;
		void Draw(sf::RenderWindow& _wnd)				override;
		void SetScale(const sf::Vector2f& _newScale)	override;

	public:
		const sf::Vector2u& GetPos() const;
		void SetNewSize(const sf::Vector2f& _newSize);
		const sf::Vector2f GetSize() const;

	private:
		void changeRotation(const sf::Vector2u& _newPos);
	};

};

#endif

