#ifndef LOGICFIELD_H
#define LOGICFIELD_H

#include <memory>
#include <SFML/System.hpp>

#include "LevelConstructor.h"

namespace Logic
{
	class LogicField
	{
	private:
		std::shared_ptr<LVLConstructor::Level> curlvl;

	private:
		sf::Vector2u applePos;

	public:
		LogicField(std::shared_ptr<LVLConstructor::Level> _lvl);

	public:
		LogicField(const LogicField&) = delete;
		LogicField& operator=(const LogicField&) = delete;

	public:
		bool checkOnEmpty(const sf::Vector2u& _pos);
		bool CheckSnakeGowUp(const sf::Vector2u& _pos);

		bool SetApple(const sf::Vector2u& _applePos);

	private:
		bool checkFieldLimits(const sf::Vector2u& _pos);
	};

}
#endif