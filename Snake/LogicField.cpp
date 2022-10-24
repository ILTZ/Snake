#include "LogicField.h"
#include "SnakeBody.h"

using namespace Logic;

bool Logic::LogicField::SetApple(const sf::Vector2i& _applePos)
{
	if (checkFieldLimits(_applePos))
	{
		if (curlvl->GetBlock(_applePos.x, _applePos.y) == LVLConstructor::LVLblock::FLOR &&
			!checkIntersectionWithPawn(_applePos))
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

Logic::LogicField::LogicField(
	std::shared_ptr<LVLConstructor::Level> _lvl,
	std::shared_ptr<Snake::SnakeBody> _snake) :
	curlvl{_lvl}, 
	snake{_snake},
	lvlW{_lvl->GetConfigs().width},
	lvlH{_lvl->GetConfigs().height}
{

}

bool Logic::LogicField::checkOnEmpty(const sf::Vector2i& _pos)
{
	if (checkFieldLimits(_pos))
	{
		if (curlvl->GetBlock(_pos.x, _pos.y) == LVLConstructor::LVLblock::FLOR)
			return true;
	}
	else
	{
		relocSnake(_pos);
		return true;
	}

	return false;
}

bool Logic::LogicField::CheckSnakeGowUp(const sf::Vector2i& _pos)
{
	if (_pos.x == applePos.x && _pos.y == applePos.y)
		return true;

	return false;
}

bool Logic::LogicField::checkFieldLimits(const sf::Vector2i& _pos)
{
	if (_pos.x < 0 || _pos.y < 0)
		return false;

	if (static_cast<unsigned int>(_pos.x) < curlvl->GetConfigs().width &&
		static_cast<unsigned int>(_pos.y) < curlvl->GetConfigs().height)
	{	
		return true;
	}

	return false;
}

bool Logic::LogicField::checkIntersectionWithPawn(const sf::Vector2i& _obj)
{
	for (size_t i = 0; i < snake->GetCurLen(); ++i)
	{
		if (_obj == snake->GetPosOnIndex(static_cast<unsigned int>(i)))
			return true;
	}

	return false;
}

void Logic::LogicField::relocSnake(const sf::Vector2i& _curCoords)
{
	sf::Vector2i tempVec = _curCoords;

	if (_curCoords.x < 0)
		tempVec.x = static_cast<int>(lvlW - 1u);
	else if (static_cast<unsigned int>(_curCoords.x) > lvlW - 1u)
		tempVec.x = 0;

	if (_curCoords.y < 0)
		tempVec.y = static_cast<int>(lvlH - 1u);
	else if (static_cast<unsigned int>(_curCoords.y) > lvlH - 1u)
		tempVec.y = 0;

	snake->SetPos(tempVec);
}

bool Logic::LogicField::CheckSnakeCollisions()
{
	sf::Vector2i head = snake->GetHeadPos();
	for (size_t i = 1; i < snake->GetCurLen(); ++i)
	{
		if (head == snake->GetPosOnIndex(static_cast<unsigned int>(i)))
			return true;
	}

	return false;
}
