#include "Timer.h"

Timer::Timer() : tempTime{0.f}
{
    last = std::chrono::steady_clock::now();
}

float Timer::Mark()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;

	return frameTime.count();
}

float Timer::Peek() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}

bool Timer::CheckInterval(float _nTime)
{
	tempTime += Peek();
	if (tempTime >= _nTime)
	{
		last = std::chrono::steady_clock::now();
		tempTime = 0.f;
		return true;
	}

	return false;
}
