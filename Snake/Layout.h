#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <memory>

#include "BaseDrawable.h"

namespace LAYOUT
{
	enum class Position
	{
		MIDLE	= 0,
		RIGHT	= 1,
		LEFT	= 2,
	};

	class Layout final : BaseDrawable
	{
	private:
		std::vector<std::shared_ptr<BaseDrawable>> drawVector;

	public:
		Layout(const sf::Vector2f& _size, const sf::Vector2f& _pos);

	public:
		Layout(const Layout&)				= delete;
		Layout(Layout&&)					= delete;
		Layout& operator=(const Layout&)	= delete;
		Layout& operator=(Layout&&)			= delete;

	public:
		void AddObject(std::shared_ptr<BaseDrawable> _drawableObj);
		void SetObjRelativePosition(Position _pos);


	public:
		virtual void SetPosition(const sf::Vector2f& _newPos)	override;
		virtual void SetScale(const sf::Vector2f& _newScale)	override;
		virtual void Draw(sf::RenderWindow& _wnd)				override;

	private:
		void relocateObjcts();

		void setObjctsScale(const sf::Vector2f& _newScale);

	private:
		const float calculateHeightSize(const std::vector<std::shared_ptr<BaseDrawable>>& _vec);

		void transformObjcts();
	};
}

#endif

