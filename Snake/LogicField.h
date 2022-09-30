#ifndef LOGICFIELD_H
#define LOGICFIELD_H

#include <SFML/System.hpp>

#include "LevelConstructor.h"
#include "BasePawn.h"


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
		LogicField					(std::shared_ptr<LVLConstructor::Level> _lvl);

	public:
		LogicField					(const LogicField&) = delete;
		LogicField& operator=		(const LogicField&) = delete;

	public:
		bool checkOnEmpty			(const sf::Vector2u& _pos);
		bool CheckSnakeGowUp		(const sf::Vector2u& _pos);
		bool SetApple				(const sf::Vector2u& _applePos);
		bool CheckSnakeCollisions	(std::shared_ptr<BaseP::BasePawn> _snake);

	public:
		const unsigned int GetLVLW() const;
		const unsigned int GetLVLH() const;

	private:
		bool checkFieldLimits(const sf::Vector2u& _pos);
		
	};

}
#endif