#ifndef SNAKE_PART_H
#define SNAKE_PART_H

#include "DrawableCircle.h"
#include "MoveOnBoardBaseObj.h"

class SnakePart final : public DrawableCircle, public MoveOnBoardBaseObj
{
private:

public:
	SnakePart(const char* _pathToText, float _radius = 20.f);
	SnakePart(const SnakePart& _other);
	SnakePart(SnakePart&& _other)				noexcept;

public:
	void SetPos(const sf::Vector2u& _newPos)		override;
	void SetScale(const sf::Vector2f& _newScale)	override;

private:
	const sf::Vector2f calculateCurrentWindowPos(const sf::Vector2u& _fieldPos);
};


#endif

