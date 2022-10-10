#ifndef APPLE_H
#define APPLE_H

#include "MoveOnBoardBaseObj.h"
#include "BaseScalable.h"
#include "DrawableCircle.h"


class Apple : public DrawableCircle, public BaseScalable, public MoveOnBoardBaseObj
{
private:


public:
	Apple(const char* _pathToText);

public:
	Apple(const Apple&)				= delete;
	Apple& operator=(const Apple&)	= delete;

	void CalculateAndSetScale(const ScaleDeterminant& _det) override;

	void SetPos(const sf::Vector2u& _newPos) override;

private:

};


#endif
