#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <vector>

#include "SnakeParticle.h"
#include "BaseD.h"

namespace Snake
{
	enum class Direction
	{
		TOP = 0,
		DOWN = 1,
		RIGHT = 2,
		LEFT = 3
	};

	class SnakeBody : public BaseD
	{
	private:
		std::string headTPath;
		std::string torsoTPath;

	private:
		int xDir = 0;
		int yDir = 0;

	private:
		bool firstMove = false;
		const int snakeStartSize = 4;

	private:
		std::vector<SmartPointer::SmartPointer<SnakePart::SnakeParticle>> body;

	private:
		int curLength = 0;

	public:
		SnakeBody(const char* _pathToHead, const char* _pathToBody);

	public:
		SnakeBody(const SnakeBody&) = delete;
		SnakeBody& operator=(const SnakeBody&) = delete;

	public:
		void Draw(sf::RenderWindow& _wnd) override;

	public:
		void Move();
		void SetDir(Direction _dir);
		void GrowUp();
		void SetPos(const sf::Vector2f& _pos);

	public:
		void SetSpriteScale(int _width, int _height) override{};

	private:
		void clearBody();
		void fillBody(int _count, const char* _pathToHead, const char* _pathToTorso);
		void addTorsoSection(const char* _pathToTorso);
	};
}

#endif

