#include "Apple.h"

Apple::Apple(const char* _pathToText) : DrawableCircle(_pathToText)
{

}

void Apple::CalculateAndSetScale(const ScaleDeterminant& _det)
{
	DrawableCircle::SetScale(
		_det.CalculateScaleForGameObject(sf::Vector2f(
			baseFigure->getRadius() * 2.f, 
			baseFigure->getRadius() * 2.f))
		);
}

void Apple::SetPos(const sf::Vector2u& _newPos)
{
	currentBoardPosition = _newPos;
	DrawableCircle::SetPosition(calculateCurrentWindowPos(currentBoardPosition));
}


