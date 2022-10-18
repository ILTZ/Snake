#ifndef NAME_WIDGET_H
#define NAME_WIDGET_H

#include "InfoWidget.h"

class NameWidget : public InfoWidget
{
private:
	const unsigned int letterSize	= 15;
	std::string name				= "Reserved";
	unsigned int points				= 0;
	const char separateSymbol		= '-';

public:
	NameWidget(
		const char* _pathToTexture,
		const char* _pathToFont,
		const char* _name = nullptr,
		unsigned int _points = 0u);
	NameWidget(const NameWidget& _other)	= delete;
	NameWidget(NameWidget&& _other)			noexcept;

public: 
	virtual void Draw(sf::RenderWindow& _wnd)					override;
	virtual void SetScale(const sf::Vector2f& _newScale)		override;
	virtual void SetPosition(const sf::Vector2f& _newPosition)	override;

public:
	void SetName(const char* _name);
	void SetPoints(unsigned int _points);

private:
	const std::string getString() const;
};


#endif

