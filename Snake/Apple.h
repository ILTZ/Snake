#ifndef APPLE_H
#define APPLE_H

#include "BaseDrawable.h"
#include "BaseD.h"

class Apple : public BaseDrawable::BaseDrawableCircle
{
private:


public:
	Apple(const char* _pathToText);

public:
	Apple(const Apple&)				= delete;
	Apple& operator=(const Apple&)	= delete;

private:

};


#endif
