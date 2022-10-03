#include "Apple.h"

Apple::Apple(const char* _pathToText) : BaseDrawableCircle(_pathToText)
{

}

void Apple::CalculateAndSetScale(const ScaleDeterminant& _det)
{
	BaseDrawableCircle::SetScale(
		_det.CalculateScaleForGameObject(sf::Vector2f(
			baseFigure->getRadius() * 2.f, 
			baseFigure->getRadius() * 2.f))
		);
}


