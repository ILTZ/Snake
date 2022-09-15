#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <vector>
#include "SnakeParticle.h"

namespace Snake
{
	enum class Direction
	{
		TOP = 0,
		DOWN = 1,
		RIGHT = 2,
		LEFT = 3
	};

	class SnakeBody
	{
	private:
		std::vector<SmartPointer::SmartPointer<SnakePart::SnakeParticle>> body;

	private:
		int curLength = 0;

	public:
		SnakeBody();

	public:
		SnakeBody(const SnakeBody&) = delete;
		SnakeBody& operator=(const SnakeBody&) = delete;

	public:
		void Draw(const sf::RenderWindow& _wnd) const;

	public:
		void Move();
		void SetDir(Direction _dir);

	private:
		void clearBody();
	};
}

#endif

