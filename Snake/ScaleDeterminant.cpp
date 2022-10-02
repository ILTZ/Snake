#include "ScaleDeterminant.h"

const sf::Vector2f ScaleDeterminant::CalculateScale(
    const sf::Vector2f& _fieldSize, 
    const sf::Vector2f& _fieldCellSize, 
    const sf::Vector2f& _drawableObjSize) const
{
    float xFactor = 1.f;
    float yFactor = 1.f;


    if (_drawableObjSize.x * _fieldCellSize.x > _fieldSize.x)
    {
        xFactor = _fieldSize.x / (_drawableObjSize.x * _fieldCellSize.x);
    }
    if (_drawableObjSize.y * _fieldCellSize.y > _fieldSize.y)
    {
        yFactor = _fieldSize.y / (_drawableObjSize.y * _fieldCellSize.y - _fieldSize.y);
    }

    return sf::Vector2f(xFactor, yFactor);
}
