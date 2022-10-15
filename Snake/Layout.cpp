#include "Layout.h"

LAYOUT::Layout::Layout(const sf::Vector2f& _size, const sf::Vector2f& _pos)
{
	currentScale		= { 1.f,1.f };
	currentSize			= _size;
	currentPosition		= _pos;


	borders = std::make_unique<sf::RectangleShape>(_size);
	borders->setOrigin(_size / 2.f);
	borders->setFillColor(sf::Color(0u, 0u, 0u, 0u));
	borders->setPosition(currentPosition);
	borders->setOutlineColor(sf::Color::Red);
	borders->setOutlineThickness(1.f);
}

void LAYOUT::Layout::AddObject(std::shared_ptr<BaseDrawable> _drawableObj)
{
	drawVector.push_back(_drawableObj);
	drawVector.back()->SetScale(currentScale);

	rerangeObjcts();
}

void LAYOUT::Layout::ClearLayout()
{
	drawVector.clear();
}

void LAYOUT::Layout::SetDistanceBeetwenObjcts(float _newDistance)
{
	distanceBetweenObjcts = _newDistance;

	rerangeObjcts();
}

void LAYOUT::Layout::alignOn(Position _pos)
{
	currentAlign;

	rerangeObjcts();
}

void LAYOUT::Layout::SetPosition(const sf::Vector2f& _newPos)
{
	currentPosition = _newPos;
	borders->setPosition(_newPos);

	rerangeObjcts();
}

void LAYOUT::Layout::SetScale(const sf::Vector2f& _newScale)
{
	currentScale = _newScale;

	for (auto& el : drawVector)
		el->SetScale(_newScale);

	rerangeObjcts();
}

void LAYOUT::Layout::Draw(sf::RenderWindow& _wnd)
{
	for (auto& el : drawVector)
	{
		el->Draw(_wnd);
	}
	_wnd.draw(*borders.get());
}

void LAYOUT::Layout::rerangeObjcts()
{
	sf::Vector2f startPos;
	startPos.x = currentPosition.x;

	switch (currentAlign)
	{
	case LAYOUT::Position::MIDLE:
		startPos.y = currentPosition.y - (sumObjctsHeight() / 2.f);
		break;

	case LAYOUT::Position::TOP:
		startPos.y = currentPosition.y - (currentSize.y / 2.f);
		break;

	case LAYOUT::Position::BOT:
		startPos.y = currentPosition.y + (currentSize.y / 2.f) - sumObjctsHeight();
		break;

	default:
		break;
	}

	for (auto& el : drawVector)
	{
		startPos.y += el->GetSize().y / 2.f;

		el->SetPosition(startPos);

		startPos.y += (el->GetSize().y / 2.f + distanceBetweenObjcts);
	}
}

const float LAYOUT::Layout::sumObjctsHeight() const
{
	float sumHeight = 0.f;

	for (auto& el : drawVector)
		sumHeight += el->GetSize().y;

	sumHeight += (static_cast<float>(drawVector.size()) * distanceBetweenObjcts);

	return sumHeight;
}




