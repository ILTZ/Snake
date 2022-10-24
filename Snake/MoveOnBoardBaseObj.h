#ifndef MOBBO_H
#define MOBBO_H

#include <SFML/System/Vector2.hpp>

class MoveOnBoardBaseObj
{
protected:
	sf::Vector2i currentBoardPosition;

public:
	virtual ~MoveOnBoardBaseObj() {};

	virtual const sf::Vector2i GetPos()	const			{ return currentBoardPosition; }
	virtual void SetPos(const sf::Vector2i& _newPos)	{ currentBoardPosition = _newPos; }

};



#endif

