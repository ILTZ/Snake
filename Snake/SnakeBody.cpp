#include "SnakeBody.h"

using namespace Snake;

Snake::SnakeBody::SnakeBody(const char* _pathToHead, const char* _pathToBody) :
	headTPath{_pathToHead}, torsoTPath{_pathToBody}
{
	fillBody(snakeStartSize, headTPath.c_str(), torsoTPath.c_str());
}

void Snake::SnakeBody::Draw(sf::RenderWindow& _wnd) const
{
	for (auto& el : body)
	{
		el->Draw(_wnd);
	}
}

void Snake::SnakeBody::Move()
{
	if (!firstMove)
		return;

	// From end to start of a body..
	for (size_t i = body.size() - 1; i > 0; --i)
	{
		body[i]->SetPos(sf::Vector2f(
			body[i - 1]->GetPos().x,
			body[i - 1]->GetPos().y
		));
	}

	body[0]->SetPos(sf::Vector2f(
		body[0]->GetPos().x + static_cast<float>(xDir),
		body[0]->GetPos().y + static_cast<float>(yDir)
	));
}

void Snake::SnakeBody::SetDir(Direction _dir)
{
	if (!firstMove)
		firstMove = true;

	switch (_dir)
	{
	case Snake::Direction::TOP:
		if (yDir != -1 && yDir != 1)
		{
			yDir = 1;
			xDir = 0;
		}
		break;

	case Snake::Direction::DOWN:
		if (yDir != 1 && yDir != -1)
		{
			yDir = -1;
			xDir = 0;
		}
		break;

	case Snake::Direction::RIGHT:
		if (xDir != 1 && xDir != -1)
		{
			xDir = 1;
			yDir = 0;
		}
		break;

	case Snake::Direction::LEFT:
		if (xDir != -1 && xDir != 1)
		{
			xDir = -1;
			yDir = 0;
		}
		break;

	default:
		break;
	}
}

void Snake::SnakeBody::GrowUp()
{
	addTorsoSection(torsoTPath.c_str());
}

void Snake::SnakeBody::SetPos(const sf::Vector2f& _pos)
{
	for (int i = 0; i < body.size(); ++i)
	{
		body[i]->SetPos(sf::Vector2f(
			_pos.x,
			_pos.y + static_cast<float>(i)
		));
	}
}

void SnakeBody::clearBody()
{
	if (!body.empty())
		body.clear();
}

void Snake::SnakeBody::fillBody(int _count, const char* _pathToHead, const char* _pathToTorso)
{
	body.clear();

	for (int i = 0; i < _count; ++i)
	{
		if (i < 1)
		{
			body.emplace_back(new SnakePart::SnakeParticle(_pathToHead));
			body.back()->SetPos(sf::Vector2f());
			continue;
		}

		body.emplace_back(new SnakePart::SnakeParticle(_pathToTorso));
		body.back()->SetPos(sf::Vector2f());
	}

}

void Snake::SnakeBody::addTorsoSection(const char* _pathToTorso)
{
	if (_pathToTorso)
	{
		body.emplace_back(new SnakePart::SnakeParticle(_pathToTorso));
		body.back()->SetPos(sf::Vector2f(
			body[body.size() - 1]->GetPos().x, 
			body[body.size() - 1]->GetPos().y));
	}
}
