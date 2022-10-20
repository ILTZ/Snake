#ifndef INPUT_NAME_WIDGET_H
#define INPUT_NAME_WIDGET_H

#include "InfoWidget.h"

class InputNameWidget : public InfoWidget
{
private:
	std::string name;
	std::string::iterator letterIt;
	const char separateSymbol	= '-';
	const char backspaceSymbol	= '\b';
	const unsigned int maxLetters = 10;
	

public:
	InputNameWidget(
		const char* _pathToText,
		const char* _pathToFont);
	InputNameWidget(InputNameWidget&& _other) noexcept;

public:
	InputNameWidget(const InputNameWidget&)				= delete;
	InputNameWidget& operator=(const InputNameWidget&)	= delete;

public:
	virtual void Draw(sf::RenderWindow& _wnd)					override;
	virtual void SetScale(const sf::Vector2f& _newScale)		override;
	virtual void SetPosition(const sf::Vector2f& _newPosition)	override;

public:
	void AddSymbol(char _symbol);
	void RemoveSymbol();

	const std::string GetString() const;

private:


};


#endif

