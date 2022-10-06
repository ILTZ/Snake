#include "InfoWidget.h"

InfoWidget::InfoWidget(const char* _pathToTexture, const char* _pathToFont) :
	BaseWidget{_pathToTexture}
{
	widgetText = new BaseText(
		_pathToFont,
		std::string("NONE"),
		static_cast<unsigned int>(rectangleShape->getSize().y / 2.5f),
		sf::Color::Red,
		sf::Text::Italic
	);
}

InfoWidget::InfoWidget(InfoWidget&& _other) noexcept :
	BaseWidget{std::move(_other)}, widgetText{_other.widgetText.Release()}
{

}


