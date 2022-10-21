#ifndef LEADER_RECORD_WIDGET_H
#define LEADER_RECORD_WIDGET_H

#include "InfoWidget.h"

class LeaderRecordWidget : public InfoWidget
{
private:
	const size_t baseNameSize		= 10;
	const size_t letterSize			= 25;
	std::string name;
	std::string points;
	std::string timeAsString;

	const char separateSymbol		= '-';
	
	bool valid						= false;

public:
	LeaderRecordWidget(
		const char* _pathToTexture,
		const char* _pathToFont,
		const char* _name			= nullptr,
		const std::string& _points	= "0",
		const std::string& _time	= "00:00");
	LeaderRecordWidget(const LeaderRecordWidget& _other)	= delete;
	LeaderRecordWidget(LeaderRecordWidget&& _other)			noexcept;

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

