#ifndef SCALE_DETERMINANT_H
#define SCALE_DETERMINANT_H

#include <SFML/System/Vector2.hpp>

class ScaleDeterminant
{
private:
	const sf::Vector2u gameFieldSize;
	const sf::Vector2u gameFieldSizeOnCell;

public:
	ScaleDeterminant(const sf::Vector2u& _gameFieldSize, const sf::Vector2u& _gameFieldSizeOnCell);
	
public:
	ScaleDeterminant(const ScaleDeterminant&)				= delete;
	ScaleDeterminant(ScaleDeterminant&&)					= delete;

	ScaleDeterminant& operator=(const ScaleDeterminant&)	= delete;
	ScaleDeterminant& operator=(ScaleDeterminant&&)			= delete;

public:
	const sf::Vector2f CalculateScale(const sf::Vector2f& _drawableObjSize) const;

private:


};


#endif
