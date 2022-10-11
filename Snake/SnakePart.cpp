#include "SnakePart.h"

SnakePart::SnakePart(const char* _pathToText) :
	DrawableCircle{_pathToText}
{
}

SnakePart::SnakePart(const SnakePart& _other) : 
	DrawableCircle{_other}
{
	currentBoardPosition = _other.currentBoardPosition;
}

SnakePart::SnakePart(SnakePart&& _other) noexcept :
	DrawableCircle{std::move(_other)}
{
	currentBoardPosition = _other.currentBoardPosition;
}

void SnakePart::SetPos(const sf::Vector2u& _newPos)
{
	currentBoardPosition = _newPos;
	DrawableCircle::SetPosition(calculateCurrentWindowPos(currentBoardPosition));
}

void SnakePart::SetScale(const sf::Vector2f& _newScale)
{
	DrawableCircle::SetScale(_newScale);
	DrawableCircle::SetPosition(calculateCurrentWindowPos(currentBoardPosition));
}


