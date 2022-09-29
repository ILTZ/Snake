#ifndef GRAPHICFIELD_H
#define GRAPHICFIELD_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>

#include "BaseD.h"
#include "SmartPointer.h"
#include "LevelConstructor.h"

namespace GraphicField
{
	class GraphicField : public BaseD
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
		void Draw(sf::RenderWindow& _wnd) override;
		void SetSpriteScale(unsigned int _width, unsigned int _height,
			unsigned int _lwlW, unsigned int _lwlH) override;

	private:
		// no need
		virtual void SetPos(const sf::Vector2u& _pos) override {};

	};
}

#endif