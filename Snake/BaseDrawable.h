#ifndef BASE_DRAWABLE_H
#define BASE_DRAWABLE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class BaseDrawable
{
protected:
	sf::Vector2f currentPosition;
	sf::Vector2f currentScale;

public:
	virtual void SetPosition(const sf::Vector2f& _newPos)	= 0;
	virtual void SetScale(const sf::Vector2f& _newScale)	= 0;
	virtual void Draw(sf::RenderWindow& _wnd)				= 0;

	virtual const sf::Vector2f GetPosition()	const { return currentPosition; }
	virtual const sf::Vector2f GetScale()		const { return currentScale; }

	virtual ~BaseDrawable() {};

private:
	
};



#endif // !BASE_DRAWABLE_H

