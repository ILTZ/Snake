#ifndef TIME_WIDGET_H
#define TIME_WIDGET_H

#include "Widget.h"
#include "Timer.h"
#include "BaseText.h"

class TimeWidget : public BaseWidget
{
private:
	Timer time;
	const float timerInterval;
	SmartPointer::SmartPointer<BaseText> timeText;

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

	void WorkCycle(bool _isWork);

private:
	std::string timeToString();
	void increaseTime();
};


#endif

