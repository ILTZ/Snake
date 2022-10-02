#include "ScaleDeterminant.h"

const sf::Vector2f ScaleDeterminant::CalculateScale(
    const sf::Vector2f& _windowSize, 
    const sf::Vector2f& _fieldSize, 
    const sf::Vector2f& _fieldCellSize, 
    const sf::Vector2f& _drawableObjSize) const
{
    float xFactor = 1.f;
    float yFactor = 1.f;

    const sf::Vector2f gameFieldSize = _windowSize - _fieldSize;

    if (_drawableObjSize.x * _fieldCellSize.x > gameFieldSize.x)
    {
        xFactor = gameFieldSize.x / (_drawableObjSize.x * _fieldCellSize.x - gameFieldSize.x);
    }
    if (_drawableObjSize.y * _fieldCellSize.y > gameFieldSize.y)
    {
        yFactor = gameFieldSize.y / (_drawableObjSize.y * _fieldCellSize.y - gameFieldSize.y);
    }

    return sf::Vector2f(xFactor, yFactor);
}
