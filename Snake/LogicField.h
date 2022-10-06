#ifndef LOGICFIELD_H
#define LOGICFIELD_H

#include <SFML/System.hpp>

#include "LevelConstructor.h"
#include "SnakeBody.h"
#include "BasePawn.h"


namespace Logic
{
	class LogicField
	{
	private:
		std::shared_ptr<LVLConstructor::Level>	curlvl;
		std::shared_ptr<Snake::SnakeBody>		snake;

	private:
		sf::Vector2u applePos;

	private:
		const unsigned int lvlW;
		const unsigned int lvlH;

	public:
		LogicField					(std::shared_ptr<LVLConstructor::Level> _lvl, 
									std::shared_ptr<Snake::SnakeBody> _snake);

	public:
		LogicField					(const LogicField&) = delete;
		LogicField& operator=		(const LogicField&) = delete;

	public:
		bool checkOnEmpty			(const sf::Vector2u& _pos);
		bool CheckSnakeGowUp		(const sf::Vector2u& _pos);
		bool SetApple				(const sf::Vector2u& _applePos);
		bool CheckSnakeCollisions	();

	public:
		const unsigned int GetLVLW() const;
		const unsigned int GetLVLH() const;

	private:
		bool checkFieldLimits(const sf::Vector2u& _pos);
		bool checkIntersectionWithPawn(const sf::Vector2u& _obj);
	};

}
#endif