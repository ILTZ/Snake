#include "Widget.h"

BaseWidget::BaseWidget(const char* _pathToText) : mainTexture{new sf::Texture()}
{
	mainTexture->loadFromFile(_pathToText);

	const float xSize = static_cast<float>(mainTexture->getSize().x);
	const float ySize = static_cast<float>(mainTexture->getSize().y);

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(sf::Vector2f(xSize, ySize));
	rectangleShape->setOrigin(xSize / 2.f, ySize / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

BaseWidget::BaseWidget(const BaseWidget& _other) : mainTexture{new sf::Texture(*_other.mainTexture)}
{
	const float xSize = static_cast<float>(mainTexture->getSize().x);
	const float ySize = static_cast<float>(mainTexture->getSize().y);

	rectangleShape = new sf::RectangleShape();
	rectangleShape->setSize(sf::Vector2f(xSize, ySize));
	rectangleShape->setOrigin(xSize / 2.f, ySize / 2.f);

	rectangleShape->setTexture(&*mainTexture);
}

BaseWidget::BaseWidget(BaseWidget&& _other) noexcept
{
	if (this != &_other)
	{
		mainTexture		= _other.mainTexture.Release();
		rectangleShape	= _other.rectangleShape.Release();
	}
}
