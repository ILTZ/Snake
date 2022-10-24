#ifndef SNAKE_PART_H
#define SNAKE_PART_H

#include "DrawableCircle.h"
#include "MoveOnBoardBaseObj.h"

class SnakePart final : public DrawableCircle, public MoveOnBoardBaseObj
{
private:

public:
	SnakePart(const char* _pathToText);
	SnakePart(const SnakePart& _other);
	SnakePart(SnakePart&& _other)				noexcept;

public:
	void SetPos(const sf::Vector2i& _newPos)		override;
	void SetScale(const sf::Vector2f& _newScale)	override;

};


#endif

