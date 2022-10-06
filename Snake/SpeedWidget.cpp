#include "SpeedWidget.h"

#include <iomanip>
#include <sstream>

SpeedWidget::SpeedWidget(const char* _pathToTexture, const char* _pathToFont) :
	InfoWidget{_pathToTexture, _pathToFont},
	speedMultiply{1.f}
{
	std::ostringstream temp;
	temp << "Speed x" << std::fixed << std::setprecision(2) << speedMultiply;

	widgetText->GetText().setFillColor(sf::Color::Green);
	widgetText->SetString(getSpeedString());
}

SpeedWidget::SpeedWidget(SpeedWidget&& _other) noexcept :
	InfoWidget{std::move(_other)},
	speedMultiply{_other.speedMultiply}
{
	
}

void SpeedWidget::IncreaseViewSpeed(float _delta)
{
	speedMultiply += _delta;
	widgetText->GetText().setString(getSpeedString());
}

void SpeedWidget::Draw(sf::RenderWindow& _target)
{
	_target.draw(*rectangleShape);
	widgetText->Draw(_target);
}

void SpeedWidget::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
	widgetText->SetScale(_newScale);
}

void SpeedWidget::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
	widgetText->SetPos(_newPosition);
}

const std::string SpeedWidget::getSpeedString() const
{
	std::ostringstream temp;
	temp << "Speed x" << std::fixed << std::setprecision(2) << speedMultiply;
	return temp.str();
}


