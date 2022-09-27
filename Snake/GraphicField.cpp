#include "GraphicField.h"

GraphicField::GraphicField::Sprite::Sprite(const char* _pTt)
{
	mainText = new sf::Texture();
	mainText->loadFromFile(_pTt);

	width = static_cast<float>(mainText->getSize().x);
	height = static_cast<float>(mainText->getSize().y);

	mainSprite = new sf::Sprite(*mainText);
}



GraphicField::GraphicField::GraphicField(std::shared_ptr<LVLConstructor::Level> _lvl) :
	curLvl{_lvl}
{
	sprites[LVLConstructor::LVLblock::FLOR] = Sprite(_lvl->GetConfigs().pathToFlor.c_str());
	sprites[LVLConstructor::LVLblock::WALL] = Sprite(_lvl->GetConfigs().pathToWall.c_str());
	sprites[LVLConstructor::LVLblock::WATER] = Sprite(_lvl->GetConfigs().pathToWater.c_str());

}

void GraphicField::GraphicField::Draw(sf::RenderWindow& _wnd)
{
	for (unsigned int i = 0; i < curLvl->GetConfigs().width; ++i)
	{
		for (unsigned int j = 0; j < curLvl->GetConfigs().height; ++j)
		{
			sprites[curLvl->GetBlock(i, j)].mainSprite->setPosition(
				sprites[curLvl->GetBlock(i, j)].width * (float)i,
				sprites[curLvl->GetBlock(i, j)].height * (float)j
			);

			_wnd.draw(*sprites[curLvl->GetBlock(i, j)].mainSprite);
		}
	}
}

void GraphicField::GraphicField::SetSpriteScale(unsigned int _width, unsigned int _height,
	unsigned int _lwlW, unsigned int _lwlH)
{
	for (auto& el : sprites)
	{
		if (el.second.width)
		{
			float deltaWidth = 1.f;
			float deltaHeight = 1.f;
			// 1/4 our window(need for hud)
			const unsigned int half = (_width / 4);

			if (((el.second.width * _lwlW) - static_cast<float>(_width)) < half)
			{
				deltaWidth = (static_cast<float>(_width) - half) / 
					(el.second.width * _lwlW);
			}
			if (el.second.height * _lwlH > _height)
			{
				deltaHeight = _height / (el.second.height * _lwlH);
			}

			el.second.mainSprite->setScale(deltaWidth, deltaHeight);
			el.second.width		*= deltaWidth;
			el.second.height	*= deltaHeight;
		}
	}

}


