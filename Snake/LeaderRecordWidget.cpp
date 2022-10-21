#include "LeaderRecordWidget.h"

LeaderRecordWidget::LeaderRecordWidget(
	const char* _pathToTexture, 
	const char* _pathToFont, 
	const char* _name,
	const std::string& _points,
	const std::string& _time) :
	InfoWidget{_pathToTexture, _pathToFont},
	name{"Reserverd"},
	points{ _points },
	timeAsString{_time}
{
	widgetText->GetText().setFillColor(sf::Color::Black);

	if (_name)
	{
		valid = true;

		name	= _name;
		points	= _points;

		widgetText->GetText().setFillColor(sf::Color::White);
	}

	widgetText->SetString(getString());
}

LeaderRecordWidget::LeaderRecordWidget(LeaderRecordWidget&& _other) noexcept :
	InfoWidget{std::move(_other)},
	letterSize{_other.letterSize},
	name{_other.name},
	points{_other.points},
	separateSymbol{_other.separateSymbol}
{
	
}

void LeaderRecordWidget::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(*rectangleShape);
	widgetText->Draw(_wnd);
}

void LeaderRecordWidget::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
	widgetText->SetScale(_newScale);
}

void LeaderRecordWidget::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
	widgetText->SetPos(_newPosition);
}

void LeaderRecordWidget::SetName(const char* _name)
{
	name = _name;

	widgetText->SetString(getString());
}

void LeaderRecordWidget::SetPoints(unsigned int _points)
{
	points = _points;

	widgetText->SetString(getString());
}

const std::string LeaderRecordWidget::getString() const
{
	if (name.size() > baseNameSize || !valid) //Its broken record
		return name;

	std::string string(letterSize, separateSymbol);
	string.replace(string.begin(), string.begin() + name.size(), name);

	const size_t sep = 2;
	string.replace(
		string.begin() + baseNameSize + sep,
		string.begin() + baseNameSize + sep + points.size(),
		points);

	string.replace(string.end() - timeAsString.size(), string.end(), timeAsString);


	return string;
}
