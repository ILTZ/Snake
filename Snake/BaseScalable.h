#ifndef BASE_SCALABLE_H
#define BASE_SCALABLE_H

#include "ScaleDeterminant.h"

class BaseScalable
{
public:

	virtual void CalculateAndSetScale(const ScaleDeterminant& _det) = 0;

	virtual ~BaseScalable() {};
};


#endif
