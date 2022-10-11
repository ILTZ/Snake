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

		sf::Vector2f layoutSize;
		sf::Vector2f objctHelpPos;

	public:
		Layout(const sf::Vector2f& _lSize);

	public:
		Layout(const Layout&)				= delete;
		Layout(Layout&&)					= delete;
		Layout& operator=(const Layout&)	= delete;
		Layout& operator=(Layout&&)			= delete;

	public:
		void AddObject();
		void SetPos(Position _pos);


	public:
		virtual void SetPosition(const sf::Vector2f& _newPos)	override;
		virtual void SetScale(const sf::Vector2f& _newScale)	override;
		virtual void Draw(sf::RenderWindow& _wnd)				override;

	private:
		void relocateObjcts();
	};
}

#endif

