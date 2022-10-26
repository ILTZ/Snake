#ifndef GRAPHIC_FIELD_H
#define GRAPHIC_FIELD_H

#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>
#include <memory>

#include "SmartPointer.h"
#include "LevelConstructor.h"
#include "BaseScalable.h"
#include "BaseDrawable.h"

namespace GraphicField
{
	class GraphicField : public BaseDrawable, public BaseScalable
	{
	private:
		struct Sprite
		{
			Sprite(const char* _pTt);
			Sprite(){};

			SmartPointer::SmartPointer<sf::Texture> mainText;
			SmartPointer::SmartPointer<sf::Sprite>	mainSprite;

			float width		= 0;
			float height	= 0;
		};

	private:
		std::unordered_map<LVLConstructor::LVLblock, Sprite> sprites;

	private:
		std::shared_ptr<LVLConstructor::Level> curLvl;

	public:
		GraphicField(std::shared_ptr<LVLConstructor::Level> _lvl);

	public:
		GraphicField(const GraphicField&)				= delete;
		GraphicField& operator=(const GraphicField&)	= delete;

	public:
		void Draw(sf::RenderWindow& _wnd)				override;
		void SetScale(const sf::Vector2f& _newScale)	override;

	public:
		void CalculateAndSetScale(const ScaleDeterminant& _det) override;

	private:
		// no need
		virtual void SetPosition(const sf::Vector2f& _newPos) override {};

	};
}

#endif