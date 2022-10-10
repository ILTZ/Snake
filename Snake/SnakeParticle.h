#ifndef SNAKEPARTICLE_H
#define SNAKEPARTICLE_H

#include <string>
#include "BaseDrawableCircle.h"

namespace SnakePart
{
	class SnakeParticle : public BDC::BaseDrawableCircle
	{
	private:
		//const std::string pathToTexture;
		//const float baseRadius = 20.f;

	public:
		SnakeParticle(const char* _pathToText, float _radius = 20.f);
		SnakeParticle(const SnakeParticle& _other);
		SnakeParticle(SnakeParticle&& _other)				noexcept;

	public:
		SnakeParticle& operator=(const SnakeParticle& _other);



	private:

	};
}


#endif 




