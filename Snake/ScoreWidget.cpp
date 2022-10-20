#include "ScoreWidget.h"

ScoreWidget::ScoreWidget(const char* _pathToTexture,
	const char* _pathToFont) :
	InfoWidget{_pathToTexture, _pathToFont},
	scores{0u}
{
	widgetText->SetString(std::string("Scores:") + std::to_string(scores));
}

ScoreWidget::ScoreWidget(ScoreWidget&& _other) noexcept :
	InfoWidget{std::move(_other)}, 
	scores{_other.scores}
{
	
}

void ScoreWidget::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(*rectangleShape);
	widgetText->Draw(_wnd);
}

void ScoreWidget::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
	widgetText->SetScale(_newScale);
}

void ScoreWidget::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
	widgetText->SetPos(_newPosition);
}

void ScoreWidget::IncreaseScores()
{
	++scores;
	widgetText->SetString(std::string("Scores:") + std::to_string(scores));
}

const unsigned int ScoreWidget::GetScores() const
{
	return scores;
}