#include "NameWidget.h"

NameWidget::NameWidget(
	const char* _pathToTexture, 
	const char* _pathToFont, 
	const char* _name,
	unsigned int _points) :
	InfoWidget{_pathToTexture, _pathToFont}
{
	widgetText->GetText().setFillColor(sf::Color::Black);

	if (_name)
	{
		name	= _name;
		points	= _points;

		widgetText->GetText().setFillColor(sf::Color::White);
	}

	widgetText->SetString(getString());
}

NameWidget::NameWidget(NameWidget&& _other) noexcept :
	InfoWidget{std::move(_other)}
{
}

void NameWidget::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(*rectangleShape);
	widgetText->Draw(_wnd);
}

void NameWidget::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
	widgetText->SetScale(_newScale);
}

void NameWidget::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
	widgetText->SetPos(_newPosition);
}

void NameWidget::SetName(const char* _name)
{
	name = _name;

	widgetText->SetString(getString());
}

void NameWidget::SetPoints(unsigned int _points)
{
	points = _points;

	widgetText->SetString(getString());
}

const std::string NameWidget::getString() const
{
	return name + std::string(letterSize - name.size(), separateSymbol) + std::to_string(points);
}
