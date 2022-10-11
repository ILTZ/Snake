#include "DrawableRectangle.h"


DrawableRectangle::DrawableRectangle(const char* _pathToText) 
	: mainTexture{new sf::Texture()}
{
	mainTexture->loadFromFile(_pathToText);

	sf::Vector2f temp{ 
		static_cast<float>(mainTexture->getSize().x) ,
		static_cast<float>(mainTexture->getSize().y) };

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(temp);
	rectangleShape->setOrigin(temp / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

DrawableRectangle::DrawableRectangle(const DrawableRectangle& _other) 
	: mainTexture{new sf::Texture(*_other.mainTexture)}
{
	sf::Vector2f temp{ 
		static_cast<float>(mainTexture->getSize().x) ,
		static_cast<float>(mainTexture->getSize().y) };

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(temp);
	rectangleShape->setOrigin(temp / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

DrawableRectangle::DrawableRectangle(DrawableRectangle&& _other) noexcept
{
	if (this != &_other)
	{
		mainTexture		= _other.mainTexture.Release();
		rectangleShape	= _other.rectangleShape.Release();

		currentPosition = _other.currentPosition;
		currentSize		= _other.currentSize;
		currentScale	= _other.currentScale;
	}
}

DrawableRectangle& DrawableRectangle::operator=(const DrawableRectangle& _other)
{
	rectangleShape.Reset();
	mainTexture.Reset();

	mainTexture = new sf::Texture(*_other.mainTexture);

	sf::Vector2f temp{ 
		static_cast<float>(mainTexture->getSize().x) ,
		static_cast<float>(mainTexture->getSize().y) };

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(temp);
	rectangleShape->setOrigin(temp / 2.f);

	rectangleShape->setTexture(&*mainTexture);

	return *this;
}

DrawableRectangle::~DrawableRectangle()
{
}

void DrawableRectangle::Draw(sf::RenderWindow& _target)
{
	_target.draw(*rectangleShape);
}

void DrawableRectangle::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
}

void DrawableRectangle::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
}

const sf::Vector2f DrawableRectangle::GetPosition() const
{
	return rectangleShape->getPosition();
}

const sf::Vector2f DrawableRectangle::GetScale() const
{
	return rectangleShape->getScale();
}

const sf::Vector2f DrawableRectangle::GetSize() const
{
	return sf::Vector2f(
		rectangleShape->getGlobalBounds().width,
		rectangleShape->getGlobalBounds().height
	);
}

void DrawableRectangle::SetSize(const sf::Vector2f _newSize)
{
	rectangleShape->setSize(_newSize);
}
