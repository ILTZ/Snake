#include "SnakePart.h"

SnakePart::SnakePart(const char* _pathToText, float _radius) :
	DrawableCircle{_pathToText, _radius}
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

const sf::Vector2f SnakePart::calculateCurrentWindowPos(const sf::Vector2u& _fieldPos)
{
	return sf::Vector2f(
		static_cast<float>(_fieldPos.x) * width + baseFigure->getRadius(),
		static_cast<float>(_fieldPos.y) * height + height / 2.f);
}
