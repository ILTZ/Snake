#ifndef APPLE_H
#define APPLE_H

#include "BaseDrawable.h"
#include "BaseD.h"

class Apple : public BaseDrawable::BaseDrawableCircle, public BaseD
{
private:


public:
	Apple(const char* _pathToText);

public:
	Apple(const Apple&)				= delete;
	Apple& operator=(const Apple&)	= delete;

public:
	virtual void Draw(sf::RenderWindow& _wnd) override;
	virtual void SetSpriteScale(unsigned int _width, unsigned int _height,
		unsigned int _lwlW, unsigned int _lwlH) override{};
	virtual void SetPos(const sf::Vector2u& _pos) override;

private:

};


#endif
