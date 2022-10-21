#include "InputNameWidget.h"

InputNameWidget::InputNameWidget(
	const char* _pathToText,
	const char* _pathToFont) :
	InfoWidget{ _pathToText, _pathToFont }
{
	name		= std::string(maxLetters, separateSymbol);
	letterIt	= name.begin();

	widgetText->GetText().setFillColor(sf::Color::White);
	widgetText->SetString(name);
}

InputNameWidget::InputNameWidget(InputNameWidget&& _other) noexcept :
	InfoWidget{std::move(_other)},
	name{_other.name},
	separateSymbol{_other.separateSymbol},
	maxLetters{_other.maxLetters}
{
	letterIt = name.begin();
}

void InputNameWidget::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(*rectangleShape);
	widgetText->Draw(_wnd);
}
void InputNameWidget::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
	widgetText->SetScale(_newScale);
}
void InputNameWidget::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
	widgetText->SetPos(_newPosition);
}

void InputNameWidget::AddSymbol(char _symbol)
{
	if (_symbol == backspaceSymbol)
	{
		RemoveSymbol();
		return;
	}
		

	if (letterIt < name.end())
	{
		*letterIt = _symbol;
		++letterIt;

		widgetText->SetString(name);
	}	
}

void InputNameWidget::RemoveSymbol()
{
	if (letterIt > name.begin() || letterIt == name.end())
	{
		--letterIt;

		*letterIt = separateSymbol;
		widgetText->SetString(name);
	}
}

const std::optional<std::string> InputNameWidget::GetString() const
{
	if (letterIt == name.begin())
		return {};

	std::string temp;
	for (std::string::const_iterator it = name.begin(); it < letterIt; ++it)
		temp.push_back(*it);
	
	return temp;
}

