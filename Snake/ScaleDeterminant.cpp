#include "ScaleDeterminant.h"

#include <cassert>

ScaleDeterminant::ScaleDeterminant(
    const sf::Vector2u& _gameFieldSize, 
    const sf::Vector2u& _gameFieldSizeOnCell) :
    gameFieldSize{_gameFieldSize}, 
    gameFieldSizeOnCell{_gameFieldSizeOnCell}
{
}

void ScaleDeterminant::SetGameFieldSize(const sf::Vector2u& _newSize)
{
    gameFieldSize = _newSize;
}

void ScaleDeterminant::SetGameFieldSizeOnCell(const sf::Vector2u& _newSize)
{
    gameFieldSizeOnCell = _newSize;
}

const sf::Vector2f ScaleDeterminant::CalculateScaleForGameObject(const sf::Vector2f& _drawableObjSize) const
{
    assert(gameFieldSize.x && gameFieldSize.y);
    assert(gameFieldSizeOnCell.x && gameFieldSizeOnCell.y);

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

const sf::Vector2f ScaleDeterminant::CalculateAbsoluteScale(const sf::Vector2u& _objectSize, const sf::Vector2u& _targetSize) const
{
    return sf::Vector2f(
        static_cast<float>(_targetSize.x) / static_cast<float>(_objectSize.x),
        static_cast<float>(_targetSize.y) / static_cast<float>(_objectSize.y)
    );

}

const sf::Vector2f ScaleDeterminant::CalculateAbsoluteScale(const sf::Vector2f& _objectSize, const sf::Vector2f& _targetSize) const
{
    return sf::Vector2f(
        _targetSize.x / _objectSize.x,
        _targetSize.y / _objectSize.y
    );
}

const float ScaleDeterminant::CalculateAbsoluteScale(const float _firstVal, const float _secondVal) const
{
    return (_firstVal / _secondVal);
}




