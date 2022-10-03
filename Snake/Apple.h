#ifndef APPLE_H
#define APPLE_H

#include "BaseDrawable.h"
#include "BaseScalable.h"


class Apple : public BaseDrawable::BaseDrawableCircle, public BaseScalable
{
private:


public:
	Apple(const char* _pathToText);

public:
	Apple(const Apple&)				= delete;
	Apple& operator=(const Apple&)	= delete;

	void CalculateAndSetScale(const ScaleDeterminant& _det) override;

private:

};


#endif
