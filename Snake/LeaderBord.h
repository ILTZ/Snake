#ifndef LEADER_BORD_H
#define LEADER_BORD_H

#include <vector>

#include "InfoWidget.h"
#include "BaseDrawable.h"

class LeaderBord : public BaseDrawable
{
private:
	unsigned int			maxSize	= 10u;
	std::vector<InfoWidget> recording;

public:
	LeaderBord(const char* _pathToImage);

public:
	LeaderBord(const LeaderBord&)				= delete;
	LeaderBord(LeaderBord&&)					= delete;

	LeaderBord& operator=(const LeaderBord&)	= delete;
	LeaderBord& operator=(LeaderBord&&)			= delete;

public:
	virtual void SetPosition(const sf::Vector2f& _newPos)	override;
	virtual void SetScale(const sf::Vector2f& _newScale)	override;
	virtual void Draw(sf::RenderWindow& _wnd)				override;

public:
	void AddRecording(const char* _recording);

};

#endif // !LEADER_BORD_H