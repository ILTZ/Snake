#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include "Widget.h"
#include "BaseText.h"

class ScoreWidget : public BaseWidget
{
private:
	unsigned int scores;
	SmartPointer::SmartPointer<BaseText> scoresText;

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

