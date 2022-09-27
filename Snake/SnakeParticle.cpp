#include "SnakeParticle.h"

using namespace SnakePart;

SnakeParticle::SnakeParticle(const char* _pathToText, float _radius) :
	BaseDrawableCircle(_pathToText, _radius)
{
			
}

SnakePart::SnakeParticle::SnakeParticle(SnakeParticle&& _other) : BaseDrawableCircle(std::move(_other))
{
}



