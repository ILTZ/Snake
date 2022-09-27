#ifndef BASEPAWN_H
#define BASEPAWN_H


namespace BaseP
{
	enum class Direction
	{
		TOP = 0,
		DOWN = 1,
		RIGHT = 2,
		LEFT = 3
	};

	class BasePawn
	{
	public:
		virtual void SetDir(BaseP::Direction _dir) = 0;
		virtual void Move() = 0;
	};
}


#endif
