#ifndef SCALE_DETERMINANT_H
#define SCALE_DETERMINANT_H

#include <SFML/System/Vector2.hpp>

class ScaleDeterminant
{
private:
	sf::Vector2u gameFieldSize;
	sf::Vector2u gameFieldSizeOnCell;

public:
	ScaleDeterminant(
		const sf::Vector2u& _gameFieldSize			= sf::Vector2u(0u, 0u),
		const sf::Vector2u& _gameFieldSizeOnCell	= sf::Vector2u(0u, 0u));
	
public:
	ScaleDeterminant(const ScaleDeterminant&)				= delete;
	ScaleDeterminant(ScaleDeterminant&&)					= delete;

	ScaleDeterminant& operator=(const ScaleDeterminant&)	= delete;
	ScaleDeterminant& operator=(ScaleDeterminant&&)			= delete;

public:
	void SetGameFieldSize(const sf::Vector2u& _newSize);
	void SetGameFieldSizeOnCell(const sf::Vector2u& _newSize);

public:
	const sf::Vector2f CalculateScale(const sf::Vector2f& _drawableObjSize) const;
	const sf::Vector2f CalculateScaleForHUD(const sf::Vector2f& _hudSize, const sf::Vector2f _targetSize) const;
	
private:


};


#endif
