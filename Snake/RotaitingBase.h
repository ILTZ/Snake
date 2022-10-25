#ifndef ROTATING_BASE_H
#define ROTATING_BASE_H


namespace ROTATING_BASE
{
	enum class Rotation
	{
		G_0		= 0,
		G_90	= 1,
		G_180	= 2,
		G_270	= 3,
	};

	class RotatingBase
	{
	protected:
		bool autoRotation			= false;
		Rotation currentRotation	= Rotation::G_0;

	public:
		virtual void SetAutoRotation(bool _auto) { autoRotation = _auto; }
		virtual void SetCurrentRotation(Rotation _rot)		= 0;

		virtual const Rotation GetCurrentRotation() const	= 0;
	};




}
#endif
