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
}

void LAYOUT::Layout::SetObjRelativePosition(Position _pos)
{
	switch (_pos)
	{
	case LAYOUT::Position::MIDLE:
		
		break;

	case LAYOUT::Position::RIGHT:
		break;

	case LAYOUT::Position::LEFT:
		break;

	default:
		break;
	}
}

void LAYOUT::Layout::SetPosition(const sf::Vector2f& _newPos)
{
	currentPosition = _newPos;
	relocateObjcts();
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

void LAYOUT::Layout::relocateObjcts()
{
	for (size_t i = 0; i < drawVector.size(); ++i)
	{
		drawVector[i]->SetPosition(sf::Vector2f(
			currentPosition.x,
			(currentPosition.y / static_cast<float>(drawVector.size() + 2)) * static_cast<float>(i + 1)));
	}
}

void LAYOUT::Layout::setObjctsScale(const sf::Vector2f& _newScale)
{
	for (auto& el : drawVector)
	{
		el->SetScale(_newScale);
	}
	relocateObjcts();
}

const float LAYOUT::Layout::calculateHeightSize(const std::vector<std::shared_ptr<BaseDrawable>>& _vec)
{
	float tempY{0.f};

	for (auto& el : drawVector)
	{
		tempY += el->GetSize().y;
	}

	return tempY;
}

void LAYOUT::Layout::transformObjcts()
{
	const float globalHeight = calculateHeightSize(drawVector);

	float yFactor = 1.f;
	float xFactor = 1.f;

	if (globalHeight > currentSize.y)
	{
		yFactor = currentSize.y / globalHeight;
	}

	for (auto& el : drawVector)
	{
		if (el->GetSize().x > currentSize.x)
		{
			xFactor = currentSize.x / el->GetSize().x;
		}
	}

	setObjctsScale(sf::Vector2f(xFactor, yFactor));
}
