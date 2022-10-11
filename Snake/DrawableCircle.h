#ifndef DRAWABLE_CIRCLE_H
#define DRAWABLE_CIRCLE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "SmartPointer.h"
#include "BaseDrawable.h"

class DrawableCircle : public BaseDrawable
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
	virtual void SetPosition(const sf::Vector2f& _newPos)	override;
	virtual void SetScale(const sf::Vector2f& _newScale)	override;
	virtual void Draw(sf::RenderWindow& _wnd)				override;

	const sf::Vector2f GetSize() const override;

protected:
	const sf::Vector2f calculateCurrentWindowPos(const sf::Vector2u& _fieldPos) const;

private:
	void changeRotation(const sf::Vector2f& _newPos);

};


#endif

