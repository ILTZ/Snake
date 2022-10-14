#include "Layout.h"

LAYOUT::Layout::Layout(const sf::Vector2f& _size, const sf::Vector2f& _pos)
{
	currentScale		= { 1.f,1.f };
	currentSize			= _size;
	currentPosition		= _pos;

}

void LAYOUT::Layout::AddObject(std::shared_ptr<BaseDrawable> _drawableObj)
{
	drawVector.push_back(_drawableObj);

	allObjctsHeight += drawVector.back()->GetSize().y;


	//drawVector.back()->SetScale(currentScale);
	setObjctsPosition(currentPosition);
}

void LAYOUT::Layout::ClearLayout()
{
	drawVector.clear();
	allObjctsHeight = 0.f;
}

void LAYOUT::Layout::SetPosition(const sf::Vector2f& _newPos)
{
	currentPosition = _newPos;
	setObjctsPosition(_newPos);
}

void LAYOUT::Layout::SetScale(const sf::Vector2f& _newScale)
{
	currentScale = _newScale;
	setObjctsScale(currentScale);
}

void LAYOUT::Layout::Draw(sf::RenderWindow& _wnd)
{
	for (auto& el : drawVector)
	{
		el->Draw(_wnd);
	}
}

void LAYOUT::Layout::setObjctsScale(const sf::Vector2f& _newScale)
{
	for (auto& el : drawVector)
	{
		el->SetScale(_newScale);
	}
}

void LAYOUT::Layout::setObjctsPosition(const sf::Vector2f& _newPosiion)
{
	for (size_t i = 0; i < drawVector.size(); ++i)
	{
		drawVector[i]->SetPosition(sf::Vector2f(
			_newPosiion.x,
			(_newPosiion.y / static_cast<float>(drawVector.size() + 2)) * static_cast<float>(i + 1)));
	}
}

void LAYOUT::Layout::checkObjSizeLimits(const std::shared_ptr<BaseDrawable>& _obj)
{
	allObjctsHeight += _obj->GetSize().y;



	if (allObjctsHeight > currentSize.y)
	{
		const float newYFactor = det.CalculateAbsoluteScale(currentSize.y, allObjctsHeight);
	}

}

void LAYOUT::Layout::transformObjcts()
{


}




