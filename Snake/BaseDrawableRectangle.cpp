#include "BaseDrawableRectangle.h"

using namespace BDR;

BaseDrawableRectangle::BaseDrawableRectangle(const char* _pathToText) : mainTexture{new sf::Texture()}
{
	mainTexture->loadFromFile(_pathToText);

	const float xSize = static_cast<float>(mainTexture->getSize().x);
	const float ySize = static_cast<float>(mainTexture->getSize().y);

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(sf::Vector2f(xSize, ySize));
	rectangleShape->setOrigin(xSize / 2.f, ySize / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

BaseDrawableRectangle::BaseDrawableRectangle(const BaseDrawableRectangle& _other) : mainTexture{new sf::Texture(*_other.mainTexture)}
{
	const float xSize = static_cast<float>(mainTexture->getSize().x);
	const float ySize = static_cast<float>(mainTexture->getSize().y);

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(sf::Vector2f(xSize, ySize));
	rectangleShape->setOrigin(xSize / 2.f, ySize / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

BaseDrawableRectangle::BaseDrawableRectangle(BaseDrawableRectangle&& _other) noexcept
{
	if (this != &_other)
	{
		mainTexture		= _other.mainTexture.Release();
		rectangleShape	= _other.rectangleShape.Release();
	}
}

BaseDrawableRectangle::~BaseDrawableRectangle()
{
}

void BaseDrawableRectangle::SetScale(const sf::Vector2f& _newScale)
{
	rectangleShape->setScale(_newScale);
}

void BaseDrawableRectangle::SetPosition(const sf::Vector2f& _newPosition)
{
	rectangleShape->setPosition(_newPosition);
}
