#include "SnakeBody.h"

using namespace Snake;

Snake::SnakeBody::SnakeBody(
	const char* _pathToHead, 
	const char* _pathToBody) :
	headTPath{_pathToHead}, 
	torsoTPath{_pathToBody}
{
	fillBody(snakeStartSize, headTPath.c_str(), torsoTPath.c_str());
}

void Snake::SnakeBody::Draw(sf::RenderWindow& _wnd) 
{
	std::lock_guard<std::mutex> lg(defMt);

	for (auto& el : body)
	{
		el.Draw(_wnd);
	}
}

void Snake::SnakeBody::SetScale(const sf::Vector2f& _newScale)
{
	for (auto& el : body)
	{
		el.SetScale(_newScale);
	}
}

void Snake::SnakeBody::Move()
{
	if (!firstMove)
		return;

	// From end to start of a body..
	for (size_t i = body.size() - 1; i > 0; --i)
	{
		body[i].SetPos(sf::Vector2i(
			body[i - 1].GetPos().x,
			body[i - 1].GetPos().y
		));
	}

	body.front().SetCurrentRotation(headRotation);
	body.front().SetPos(sf::Vector2i(
		body.front().GetPos().x + static_cast<unsigned int>(xDir),
		body.front().GetPos().y + static_cast<unsigned int>(yDir)
	));

}

void Snake::SnakeBody::SetDir(BaseP::Direction _dir)
{
	if (!firstMove)
	{
		if (_dir == BaseP::Direction::DOWN)
			return;

		firstMove = true;
	}

	switch (_dir)
	{
		case BaseP::Direction::TOP:
			if (yDir != -1 && yDir != 1)
			{
				yDir = -1;
				xDir = 0;
				headRotation = ROTATING_BASE::Rotation::G_0;
			}
			break;

		case BaseP::Direction::DOWN:
			if (yDir != 1 && yDir != -1)
			{
				yDir = 1;
				xDir = 0;
				headRotation = ROTATING_BASE::Rotation::G_180;
			}
			break;

		case BaseP::Direction::RIGHT:
			if (xDir != 1 && xDir != -1)
			{
				xDir = 1;
				yDir = 0;
				headRotation = ROTATING_BASE::Rotation::G_90;
			}
			break;

		case BaseP::Direction::LEFT:
			if (xDir != -1 && xDir != 1)
			{
				xDir = -1;
				yDir = 0;
				headRotation = ROTATING_BASE::Rotation::G_270;
			}
			break;

		default:
			break;
	}
}

void Snake::SnakeBody::DoSomeSpecifyActions()
{
	this->GrowUp();
}

void Snake::SnakeBody::CalculateAndSetScale(const ScaleDeterminant& _det)
{
	auto newHeadScale = _det.CalculateScaleForGameObject(body[0].GetSize());
	auto newTorsoScale = _det.CalculateScaleForGameObject(body[1].GetSize());

	for (size_t i = 0; i < body.size(); ++i)
	{
		if (i == 0)
		{
			body[i].SetScale(newHeadScale);
			continue;
		}
		body[i].SetScale(newTorsoScale);
	}

}

void Snake::SnakeBody::GrowUp()
{
	addTorsoSection(torsoTPath.c_str());
}

void Snake::SnakeBody::SetPos(const sf::Vector2i& _pos)
{
	body[0].SetPos(_pos);
}

sf::Vector2i const Snake::SnakeBody::GetPos() const
{
	return this->GetHeadPos();
}

void Snake::SnakeBody::SetStartPos(const sf::Vector2u& _startPos)
{
	for (unsigned int i = 0; i < body.size(); ++i)
	{
		body[i].SetPos(sf::Vector2i(
			_startPos.x,
			_startPos.y + i
		));
	}
}

const sf::Vector2i Snake::SnakeBody::GetHeadPos() const
{
	return sf::Vector2i(body[0].GetPos());
}

const sf::Vector2i Snake::SnakeBody::GetPosOnIndex(unsigned int _pos) const
{
	return body[_pos].GetPos();
}

const size_t Snake::SnakeBody::GetCurLen() const
{
	return body.size();
}

void SnakeBody::clearBody()
{
	if (!body.empty())
		body.clear();
}

void Snake::SnakeBody::fillBody(
	int _count, 
	const char* _pathToHead, 
	const char* _pathToTorso)
{
	body.clear();

	for (int i = 0; i < _count; ++i)
	{
		if (i < 1)
		{
			body.emplace_back(SnakePart(_pathToHead));
			body.back().SetAutoRotation(false);
			body.back().SetCurrentRotation(ROTATING_BASE::Rotation::G_0);
			continue;
		}

		body.emplace_back(SnakePart(_pathToTorso));
	}

}

void Snake::SnakeBody::setHeadRotatinon(ROTATING_BASE::Rotation _rot)
{
	body[0].SetCurrentRotation(_rot);
}

void Snake::SnakeBody::addTorsoSection(const char* _pathToTorso)
{
	if (_pathToTorso)
	{
		std::lock_guard<std::mutex> lg(defMt);

		sf::Vector2i pos{ 
			body[body.size() - 1].GetPos().x, 
			body[body.size() - 1].GetPos().y };
		sf::Vector2f scale = body[body.size() - 1].GetScale();

		body.emplace_back(SnakePart(_pathToTorso));
		body.back().SetPos(pos);
		body.back().SetScale(scale);
		body.back().SetAutoRotation(true);
		
	}
}
