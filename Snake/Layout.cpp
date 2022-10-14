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
	// Top edge of layout
	sf::Vector2f tempPos(currentPosition.x, currentPosition.y - (currentSize.y / 2.f));

	/*float startPos = currentPosition.y - (currentSize.y / 2.f);
	for (size_t i = 0; i < drawVector.size(); ++i)
	{
		float t = startPos + ((currentSize.y / static_cast<float>(drawVector.size() + 1)) * static_cast<float>(i + 1));
		sf::Vector2f temp
		(
			currentPosition.x,
			t
		);

		drawVector[i]->SetPosition(temp);
	}*/


	for (auto& el : drawVector)
	{
		tempPos.y += el->GetSize().y / 2.f;

		el->SetPosition(tempPos);

		tempPos.y += (el->GetSize().y / 2.f + distanceBetweenObjcts);
	}
}




