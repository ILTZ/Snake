#ifndef BASE_PLAYER_CONTROL_OBJ_H
#define BASE_PLAYER_CONTROL_OBJ_H

#include "BasePawn.h"
#include "BaseDrawable.h"

namespace Base
{
	class BasePlayerControlObj : public BaseDrawable, public BaseP::BasePawn
	{
	public:
		virtual void SetStartPos(const sf::Vector2u& _startPos) = 0;

		~BasePlayerControlObj() {};
	};
}




#endif
