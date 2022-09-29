#ifndef LOGICFIELD_H
#define LOGICFIELD_H

#include <SFML/System.hpp>

#include "LevelConstructor.h"
#include "SnakeBody.h"

namespace Logic
{
	class LogicField
	{
	private:
		std::shared_ptr<LVLConstructor::Level> curlvl;

	private:
		sf::Vector2u applePos;

	private:
		const unsigned int lvlW;
		const unsigned int lvlH;

	public:
		LogicField(std::shared_ptr<LVLConstructor::Level> _lvl);

	public:
		LogicField(const LogicField&) = delete;
		LogicField& operator=(const LogicField&) = delete;

	public:
		bool checkOnEmpty(const sf::Vector2u& _pos);
		bool CheckSnakeGowUp(const sf::Vector2u& _pos);
		bool SetApple(const sf::Vector2u& _applePos);

	public:
		const unsigned int GetLVLW() const;
		const unsigned int GetLVLH() const;

	private:
		bool checkFieldLimits(const sf::Vector2u& _pos);
		bool checkSnakeCollisions(Snake::SnakeBody* _snake);
	};

}
#endif