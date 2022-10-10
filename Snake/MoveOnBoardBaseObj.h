#ifndef MOBBO_H
#define MOBBO_H

#include <SFML/System/Vector2.hpp>

class MoveOnBoardBaseObj
{
protected:
	sf::Vector2u currentBoardPosition;

public:
	virtual ~MoveOnBoardBaseObj() {};

	virtual const sf::Vector2u GetPos()	const			{ return currentBoardPosition; }
	virtual void SetPos(const sf::Vector2u& _newPos)	{ currentBoardPosition = _newPos; }

};



#endif

