#include "ScaleDeterminant.h"

ScaleDeterminant::ScaleDeterminant(
    const sf::Vector2u& _gameFieldSize, 
    const sf::Vector2u& _gameFieldSizeOnCell) :
    gameFieldSize{_gameFieldSize}, 
    gameFieldSizeOnCell{_gameFieldSizeOnCell}
{
}

const sf::Vector2f ScaleDeterminant::CalculateScale(const sf::Vector2f& _drawableObjSize) const
{
    float xFactor = 1.f;
    float yFactor = 1.f;

    if (static_cast<unsigned int>(_drawableObjSize.x) * gameFieldSizeOnCell.x > gameFieldSize.x || 
        static_cast<unsigned int>(_drawableObjSize.x) * gameFieldSizeOnCell.x < gameFieldSize.x)
    {
        xFactor = gameFieldSize.x / (_drawableObjSize.x * gameFieldSizeOnCell.x);
    }

    if (static_cast<unsigned int>(_drawableObjSize.y) * gameFieldSizeOnCell.y > gameFieldSize.y ||
        static_cast<unsigned int>(_drawableObjSize.y) * gameFieldSizeOnCell.y < gameFieldSize.y)
    {
        yFactor = gameFieldSize.y / (_drawableObjSize.y * gameFieldSizeOnCell.y);
    }


    return sf::Vector2f(xFactor, yFactor);
}


