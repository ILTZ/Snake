#include "SnakeParticle.h"

using namespace SnakePart;

SnakeParticle::SnakeParticle(const char* _pathToText, float _radius) :
	BaseDrawable(_pathToText, _radius)
{
			
}

SnakePart::SnakeParticle::SnakeParticle(SnakeParticle&& _other) noexcept 
	: BaseDrawable(std::move(_other))
{
}

SnakePart::SnakeParticle::SnakeParticle(const SnakeParticle& _other) : BaseDrawable{_other}
{

}

SnakeParticle& SnakePart::SnakeParticle::operator=(const SnakeParticle& _other)
{

	return *this;
}



