#ifndef SPEED_WIDGET_H
#define SPEED_WIDGET_H

#include "InfoWidget.h"

class SpeedWidget : public InfoWidget
{
private:
	float speedMultiply;

public:
	SpeedWidget(const char* _pathToTexture, const char* _pathToFont);
	SpeedWidget(SpeedWidget&& _other)			noexcept;

public:
	SpeedWidget(const SpeedWidget&)				= delete;
	SpeedWidget& operator=(const SpeedWidget&)	= delete;
	
public:
	void IncreaseViewSpeed(float _delta);

public:
	void Draw(sf::RenderWindow& _target)				override;
	void SetScale(const sf::Vector2f& _newScale)		override;
	void SetPosition(const sf::Vector2f& _newPosition)	override;

private:
	const std::string getSpeedString() const;

};


#endif

