#include "InputNameWidget.h"

InputNameWidget::InputNameWidget(
	const char* _pathToText,
	const char* _pathToFont) :
	InfoWidget{ _pathToText, _pathToFont }
{
	name		= std::string(maxLetters, separateSymbol);
	letterIt	= name.begin();
	widgetText->SetString(name);
}

InputNameWidget::InputNameWidget(InputNameWidget&& _other) noexcept :
	InfoWidget{std::move(_other)}
{

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
	*letterIt = _symbol;

	if (letterIt != name.end())
		++letterIt;
}

void InputNameWidget::RemoveSymbol()
{
	*letterIt = separateSymbol;

	if (letterIt != name.end())
		--letterIt;
}

const std::string InputNameWidget::GetString() const
{
	return name;
}

