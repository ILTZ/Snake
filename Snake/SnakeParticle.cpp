#include "SnakeParticle.h"

using namespace SnakePart;

SnakeParticle::SnakeParticle(const char* _pathToText, float _radius) :
	BaseDrawableCircle(_pathToText, _radius)
{
			
}

SnakePart::SnakeParticle::SnakeParticle(SnakeParticle&& _other) noexcept 
	: BaseDrawableCircle(std::move(_other))
{
}

SnakePart::SnakeParticle::SnakeParticle(const SnakeParticle& _other) : BaseDrawableCircle{_other}
{

}

SnakeParticle& SnakePart::SnakeParticle::operator=(const SnakeParticle& _other)
{

	return *this;
}



