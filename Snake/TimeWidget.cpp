#include "TimeWidget.h"

TimeWidget::TimeWidget(
    const char* _pathToTexture, 
    const char* _pathToFont,
    float _timeInterval) :
    InfoWidget{_pathToTexture, _pathToFont},
    timerInterval{_timeInterval},
    minuts{ 0u },
    seconds{ 0u }
{
    widgetText->SetString(timeToString());
    widgetText->GetText().setFillColor(sf::Color::Cyan);
}

TimeWidget::TimeWidget(TimeWidget&& _other) noexcept : 
    InfoWidget{std::move(_other)},
    timerInterval{_other.timerInterval},
    minuts{ 0u },
    seconds{0u}
{

}

void TimeWidget::Draw(sf::RenderWindow& _wnd)
{
    _wnd.draw(*rectangleShape);
    widgetText->Draw(_wnd);
}

void TimeWidget::SetScale(const sf::Vector2f& _newScale)
{
    rectangleShape->setScale(_newScale);
    widgetText->SetScale(_newScale);
}

void TimeWidget::SetPosition(const sf::Vector2f& _newPosition)
{
    rectangleShape->setPosition(_newPosition);
    widgetText->SetPos(_newPosition);
}

void TimeWidget::WorkCycle(bool _isWork)
{
    if (!_isWork)
        return;

    if (time.CheckInterval(timerInterval))
    {
        increaseTime();
        widgetText->SetString(std::string("Time:")+
            timeToString());
    }
}

std::string TimeWidget::timeToString()
{
    std::string temp;
    if (minuts < 10u)
    {
        temp += "0";
    }
    temp += std::to_string(minuts) += ":";

    if (seconds < 10u)
    {
        temp += "0";
    }
    temp += std::to_string(seconds);

    return temp;
}

void TimeWidget::increaseTime()
{
    ++seconds;
    if (seconds == 60u)
    {
        ++minuts;
        seconds = 0u;
    }
}

