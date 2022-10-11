#include "DrawableRectangle.h"


DrawableRectangle::DrawableRectangle(const char* _pathToText) : mainTexture{new sf::Texture()}
{
	mainTexture->loadFromFile(_pathToText);

	const float xSize = static_cast<float>(mainTexture->getSize().x);
	const float ySize = static_cast<float>(mainTexture->getSize().y);

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(sf::Vector2f(xSize, ySize));
	rectangleShape->setOrigin(xSize / 2.f, ySize / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

DrawableRectangle::DrawableRectangle(const DrawableRectangle& _other) : mainTexture{new sf::Texture(*_other.mainTexture)}
{
	const float xSize = static_cast<float>(mainTexture->getSize().x);
	const float ySize = static_cast<float>(mainTexture->getSize().y);

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(sf::Vector2f(xSize, ySize));
	rectangleShape->setOrigin(xSize / 2.f, ySize / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

DrawableRectangle::DrawableRectangle(DrawableRectangle&& _other) noexcept
{
	if (this != &_other)
	{
		mainTexture		= _other.mainTexture.Release();
		rectangleShape	= _other.rectangleShape.Release();
	}
}

DrawableRectangle& DrawableRectangle::operator=(const DrawableRectangle& _other)
{
	rectangleShape.Reset();
	mainTexture.Reset();

	mainTexture = new sf::Texture(*_other.mainTexture);

	const float xSize = static_cast<float>(mainTexture->getSize().x);
	const float ySize = static_cast<float>(mainTexture->getSize().y);

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(sf::Vector2f(xSize, ySize));
	rectangleShape->setOrigin(xSize / 2.f, ySize / 2.f);

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
