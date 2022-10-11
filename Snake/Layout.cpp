#include "Layout.h"

LAYOUT::Layout::Layout(const sf::Vector2f& _lSize) :
{
	currentSize = _lSize;
	objctHelpPos = { _lSize.x / 2.f, _lSize.y };
}

void LAYOUT::Layout::SetPos(Position _pos)
{
}

void LAYOUT::Layout::SetPosition(const sf::Vector2f& _newPos)
{
}

void LAYOUT::Layout::SetScale(const sf::Vector2f& _newScale)
{
}

void LAYOUT::Layout::Draw(sf::RenderWindow& _wnd)
{
}

void LAYOUT::Layout::relocateObjcts()
{
}
