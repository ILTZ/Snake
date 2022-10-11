#ifndef INFO_WIDGET_H
#define INFO_WIDGET_H

#include "BaseText.h"
#include "DrawableRectangle.h"


class InfoWidget : public DrawableRectangle
{
protected:
	SmartPointer::SmartPointer<BaseText> widgetText;

public:
	InfoWidget(const char* _pathToTexture, const char* _pathToFont);
	InfoWidget(InfoWidget&& _other)				noexcept;

public:
	InfoWidget(const InfoWidget&)				= delete;
	InfoWidget& operator=(const InfoWidget&)	= delete;

};



#endif // !INFO_WIDGET_H




