#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point last;

private:
	std::chrono::steady_clock::time_point lastInterval;
	float tempTime;

public:
	Timer();

public:
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

public:
	float Mark();
	float Peek() const;
	bool CheckInterval(float _timeInSeconds);

private:
	float MarkForInterval();
};



#endif

