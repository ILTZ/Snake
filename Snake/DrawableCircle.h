#ifndef DRAWABLE_CIRCLE_H
#define DRAWABLE_CIRCLE_H

#include <SFML/Graphics/CircleShape.hpp>

#include "SmartPointer.h"
#include "BaseDrawable.h"
#include "RotaitingBase.h"

class DrawableCircle : public BaseDrawable, public ROTATING_BASE::RotatingBase
{
protected:
	SmartPointer::SmartPointer<sf::CircleShape>	baseFigure;
	SmartPointer::SmartPointer<sf::Texture>		baseTexture;

	float width = 0.f;
	float height = 0.f;

public:
	DrawableCircle(const char* _pathToTexture);
	DrawableCircle(const DrawableCircle& _other);
	DrawableCircle& operator=(const DrawableCircle& _other);
	DrawableCircle(DrawableCircle&& _other) noexcept;

	virtual ~DrawableCircle();

public:
	virtual void Draw(sf::RenderWindow& _target)					override;

public:
	virtual void SetCurrentRotation(ROTATING_BASE::Rotation _rot)	override;
	virtual const ROTATING_BASE::Rotation GetCurrentRotation()		const override;

public:
	virtual const sf::Vector2f GetScale()						const override;
	virtual void SetScale(const sf::Vector2f& _newScale)		override;

	virtual const sf::Vector2f GetPosition()					const override;
	virtual void SetPosition(const sf::Vector2f& _newPosition)	override;

	virtual const sf::Vector2f GetSize()						const override;
	virtual void SetSize(const sf::Vector2f _newSize)			override;

protected:
	const sf::Vector2f calculateCurrentWindowPos(const sf::Vector2i& _fieldPos) const;

private:
	void changeRotation(const sf::Vector2f& _newPos);

};


#endif

