#include "ScoreWidget.h"

ScoreWidget::ScoreWidget(const char* _pathToTexture,
	const char* _pathToFont) :
	BaseWidget{ _pathToTexture },
	scores{0u}
{
	scoresText = new BaseText(
		_pathToFont,
		std::to_string(scores),
		25u,
		sf::Color::Red,
		sf::Text::Italic
	);
}

ScoreWidget::ScoreWidget(const ScoreWidget& _other) : 
	BaseWidget{ _other }, 
	scores{ _other.scores }
{
	
}

ScoreWidget::ScoreWidget(ScoreWidget&& _other) noexcept :
	BaseWidget{std::move(_other)}, 
	scores{_other.scores},
	scoresText{_other.scoresText.Release()}
{
	
}

void ScoreWidget::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(*rectangleShape);
	scoresText->Draw(_wnd);
}

void ScoreWidget::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
	scoresText->SetScale(_newScale);
}

void ScoreWidget::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
	scoresText->SetPos(_newPosition);
}

void ScoreWidget::IncreaseScores()
{
	++scores;
	scoresText->GetText().setString(std::to_string(scores));
}

void ScoreWidget::baseScoresTextInit()
{
	
}
