#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include "InfoWidget.h"

class ScoreWidget : public InfoWidget
{
private:
	unsigned int scores;

public:
	ScoreWidget(
		const char* _pathToTexture,
		const char* _pathToFont);
	ScoreWidget(const ScoreWidget& _other)	= delete;
	ScoreWidget(ScoreWidget&& _other)		noexcept;

public:
	void Draw(sf::RenderWindow& _wnd)					override;
	void SetScale(const sf::Vector2f& _newScale)		override;
	void SetPosition(const sf::Vector2f& _newPosition)	override;

	void IncreaseScores();

};


#endif

