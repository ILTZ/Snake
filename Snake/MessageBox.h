#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <SFML/Graphics/Sprite.hpp>

#include "Button.h"
#include "BaseText.h"

class MessageBox 
{
private:
	sf::RenderTarget* parent;

private:
	sf::Texture text;
	sf::Sprite	boxSprite;

public:
	MessageBox(
		const std::string& _msg, 
		sf::RenderTarget& _parent);
	MessageBox(MessageBox&& _other)				noexcept;

public:
	MessageBox(const MessageBox&)				= delete;
	MessageBox& operator=(const MessageBox&)	= delete;
	MessageBox& operator=(MessageBox&&)			= delete;

public:
	const sf::Vector2f GetScale()						const;
	void SetScale(const sf::Vector2f& _newScale)		;

	const sf::Vector2f GetPosition()					const;
	void SetPosition(const sf::Vector2f& _newPosition)	;

	const sf::Vector2f GetSize()						const;
	void SetSize(const sf::Vector2f _newSize)			;

	const bool CheckBtn(float _x, float _y) const;

private:
	


};




#endif