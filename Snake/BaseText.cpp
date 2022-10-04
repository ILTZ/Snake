#include "BaseText.h"

BaseText::BaseText(
	const char* _pathToFont, 
	const std::string& _text, 
	unsigned int _characterSize, 
	sf::Color _color,
	sf::Text::Style _style)
{
	font.loadFromFile(_pathToFont);

	message.setString(_text);
	message.setFont(font);
	message.setCharacterSize(_characterSize);
	message.setFillColor(_color);
	message.setStyle(sf::Text::Italic);

	message.setOrigin(
		message.getGlobalBounds().width / 2.f,
		message.getGlobalBounds().height);
}

sf::Text& BaseText::GetText()
{
	return message;
}

void BaseText::Draw(sf::RenderWindow& _wnd)
{
	_wnd.draw(message);
}

void BaseText::SetPos(const sf::Vector2f& _newPos)
{
	message.setPosition(_newPos);
}

void BaseText::SetScale(const sf::Vector2f& _newScale)
{
	message.setScale(_newScale);
}
