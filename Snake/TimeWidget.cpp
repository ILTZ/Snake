#include "TimeWidget.h"

TimeWidget::TimeWidget(
    const char* _pathToTexture, 
    const char* _pathToFont,
    float _timeInterval) :
    BaseWidget{_pathToTexture},
    timerInterval{_timeInterval},
    minuts{ 0u },
    seconds{ 0u }
{
    timeText = new BaseText(
        _pathToFont,
        timeToString(),
        static_cast<unsigned int>(rectangleShape->getGlobalBounds().height / 2.f),
        sf::Color::Cyan,
        sf::Text::Italic);

}

TimeWidget::TimeWidget(TimeWidget&& _other) noexcept : 
    BaseWidget{std::move(_other)},
    timerInterval{_other.timerInterval},
    timeText{_other.timeText.Release()},
    minuts{ 0u },
    seconds{0u}
{

}

void TimeWidget::Draw(sf::RenderWindow& _wnd)
{
    _wnd.draw(*rectangleShape);
    timeText->Draw(_wnd);
}

void TimeWidget::SetScale(const sf::Vector2f& _newScale)
{
    rectangleShape->setScale(_newScale);
    timeText->SetScale(_newScale);
}

void TimeWidget::SetPosition(const sf::Vector2f& _newPosition)
{
    rectangleShape->setPosition(_newPosition);
    timeText->SetPos(_newPosition);
}

void TimeWidget::WorkCycle(bool _isWork)
{
    if (!_isWork)
        return;

    if (time.CheckInterval(timerInterval))
    {
        increaseTime();
        timeText->GetText().setString(timeToString());
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

