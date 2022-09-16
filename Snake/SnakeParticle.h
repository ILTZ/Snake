#ifndef SNAKEPARTICLE_H
#define SNAKEPARTICLE_H

#include <string>
#include "BaseDrawable.h"

namespace SnakePart
{
	class SnakeParticle : public BDraw::BaseDrawableCircle
	{
	private:
		//const std::string pathToTexture;
		//const float baseRadius = 20.f;

	public:
		SnakeParticle(const char* _pathToText, float _radius = 20.f);
		SnakeParticle(const SnakeParticle&) = delete;
		SnakeParticle& operator=(const SnakeParticle&) = delete;

	private:

	};
}


#endif 




