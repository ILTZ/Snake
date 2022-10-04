#ifndef TIME_WIDGET_H
#define TIME_WIDGET_H

#include "Widget.h"
#include "Timer.h"

class TimeWidget : public BaseWidget
{
private:
	Timer time;

public:
	TimeWidget(
		const char* _pathToTexture,
		const char* _pathToFont);
	TimeWidget(const TimeWidget& _other);
	TimeWidget(TimeWidget&& _other) noexcept;

public:
	void Draw(sf::RenderWindow& _wnd)					override;
	void SetScale(const sf::Vector2f& _newScale)		override;
	void SetPosition(const sf::Vector2f& _newPosition)	override;

private:


};


#endif

