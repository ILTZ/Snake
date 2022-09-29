#include "LogicField.h"

using namespace Logic;

bool Logic::LogicField::SetApple(const sf::Vector2u& _applePos)
{
	if (checkFieldLimits(_applePos))
	{
		if (curlvl->GetBlock(_applePos.x, _applePos.y) == LVLConstructor::LVLblock::FLOR)
		{
			applePos = _applePos;

			return true;
		}
	}

	return false;
}

const unsigned int Logic::LogicField::GetLVLW() const
{
	return lvlW;
}

const unsigned int Logic::LogicField::GetLVLH() const
{
	return lvlH;
}

Logic::LogicField::LogicField(std::shared_ptr<LVLConstructor::Level> _lvl) : 
	curlvl{_lvl}, 
	lvlW{_lvl->GetConfigs().width},
	lvlH{_lvl->GetConfigs().height}
{

}

bool Logic::LogicField::checkOnEmpty(const sf::Vector2u& _pos)
{
	if (checkFieldLimits(_pos))
	{
		if (curlvl->GetBlock(_pos.x, _pos.y) == LVLConstructor::LVLblock::FLOR)
			return true;
	}

	return false;
}

bool Logic::LogicField::CheckSnakeGowUp(const sf::Vector2u& _pos)
{
	if (_pos.x == applePos.x && _pos.y == applePos.y)
		return true;

	return false;
}

bool Logic::LogicField::checkFieldLimits(const sf::Vector2u& _pos)
{
	if (_pos.x <= curlvl->GetConfigs().width &&
		_pos.y <= curlvl->GetConfigs().height)
	{	
		return true;
	}

	return false;
}

bool Logic::LogicField::checkSnakeCollisions(Snake::SnakeBody* _snake)
{
	return false;
}
