#include "ScaleDeterminant.h"

ScaleDeterminant::ScaleDeterminant(const sf::Vector2u& _gameFieldSize) : 
    gameFieldSize{_gameFieldSize}
{
}

const sf::Vector2f ScaleDeterminant::CalculateScale(
    const sf::Vector2u& _fieldCellSize, 
    const sf::Vector2f& _drawableObjSize) const
{
    float xFactor = 1.f;
    float yFactor = 1.f;

    if (_drawableObjSize.x * _fieldCellSize.x > gameFieldSize.x)
    {
        xFactor = gameFieldSize.x / (_drawableObjSize.x * _fieldCellSize.x);
    }
    if (_drawableObjSize.y * _fieldCellSize.y > gameFieldSize.y)
    {
        yFactor = gameFieldSize.y / (_drawableObjSize.y * _fieldCellSize.y - gameFieldSize.y);
    }


    return sf::Vector2f(xFactor, yFactor);
}


