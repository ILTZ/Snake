#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>

#include "BaseDrawable.h"
#include "ScaleDeterminant.h"

namespace LAYOUT
{
	enum class Position
	{
		MIDLE	= 0,
		TOP		= 1,
		BOT		= 2,
	};

	class Layout final : BaseDrawable
	{
	private:
		std::vector<std::shared_ptr<BaseDrawable>> drawVector;
		
		float distanceBetweenObjcts = 0.f;
		Position currentAlign	= Position::MIDLE;

	private:
		ScaleDeterminant det;

	public:
		Layout() = default;
		Layout(const sf::Vector2f& _size, const sf::Vector2f& _pos);

	public:
		Layout(const Layout&)				= delete;
		Layout(Layout&&)					= delete;
		Layout& operator=(const Layout&)	= delete;
		Layout& operator=(Layout&&)			= delete;

	public:
		void AddObject(std::shared_ptr<BaseDrawable> _drawableObj);
		void ClearLayout();
		void SetDistanceBeetwenObjcts(float _newDistance);

		void alignOn(Position _pos);

	public:
		const size_t GetLayoutSize() const;

	public:
		virtual void SetPosition(const sf::Vector2f& _newPos)	override;
		virtual void SetScale(const sf::Vector2f& _newScale)	override;
		virtual void Draw(sf::RenderWindow& _wnd)				override;

	private:
		void rerangeObjcts();

		const float sumObjctsHeight()			const;
		const float getDistanceBetweenObjcts()	const;
	};
}

#endif

