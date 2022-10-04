#ifndef BASETEXT_H
#define BASETEXT_H

#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class BaseText final
{
private:
	sf::Font font;
	sf::Text message;

public:
	BaseText(
		const char* _pathToFont, 
		const std::string& _text, 
		unsigned int _characterSize, 
		sf::Color _color,
		sf::Text::Style _style);

public:
	BaseText(const BaseText& _other)			= delete;
	BaseText& operator=(const BaseText& _other) = delete;
	BaseText(BaseText&& _other)					= delete;			
	BaseText& operator=(BaseText&& _other)		= delete;
	
public:
	sf::Text& GetText();

public:
	void Draw(sf::RenderWindow& _wnd);
	void SetPos(const sf::Vector2f& _newPos);
	void SetScale(const sf::Vector2f& _newScale);

};


#endif // !BASETEXT_H





