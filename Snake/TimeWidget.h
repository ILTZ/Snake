#ifndef TIME_WIDGET_H
#define TIME_WIDGET_H


#include "Timer.h"
#include "InfoWidget.h"

class TimeWidget : public InfoWidget
{
private:
	Timer time;
	const float timerInterval;

	unsigned int minuts;
	unsigned int seconds;

public:
	TimeWidget(
		const char* _pathToTexture,
		const char* _pathToFont,
		float _timeInterval);
	TimeWidget(const TimeWidget& _other)	= delete;
	TimeWidget(TimeWidget&& _other) noexcept;

public:
	void Draw(sf::RenderWindow& _wnd)					override;
	void SetScale(const sf::Vector2f& _newScale)		override;
	void SetPosition(const sf::Vector2f& _newPosition)	override;

	void WorkCycle();

	const unsigned int GetMinuts()		const;
	const unsigned int GetSeconds()		const;
	const std::string GetTimeAsString() const;

private:
	const std::string timeToString()	const;
	void increaseTime();
};


#endif

