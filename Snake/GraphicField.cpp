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
	lWidth{_lvl->GetConfigs().width}, lHeight{_lvl->GetConfigs().height}, curLvl{_lvl}
{
	sprites[LVLConstructor::LVLblock::FLOR] = Sprite(_lvl->GetConfigs().pathToFlor.c_str());
	sprites[LVLConstructor::LVLblock::WALL] = Sprite(_lvl->GetConfigs().pathToWall.c_str());
	sprites[LVLConstructor::LVLblock::WATER] = Sprite(_lvl->GetConfigs().pathToWater.c_str());

}

void GraphicField::GraphicField::Draw(sf::RenderWindow& _wnd)
{
	for (int i = 0; i < lWidth; ++i)
	{
		for (int j = 0; j < lHeight; ++j)
		{
			sprites[curLvl->GetBlock(i, j)].mainSprite->setPosition(
				sprites[curLvl->GetBlock(i, j)].width * (float)i,
				sprites[curLvl->GetBlock(i, j)].height * (float)j
			);

			_wnd.draw(*sprites[curLvl->GetBlock(i, j)].mainSprite);
		}
	}
}

void GraphicField::GraphicField::SetSpriteScale(const int _width, const int _height)
{
	for (auto& el : sprites)
	{
		if (el.second.width)
		{
			float deltaWidth = 1.f;
			float deltaHeight = 1.f;
			// 1/4 our window(need for hud)
			const unsigned int half = (_width / 4);

			if (((el.second.width * lWidth) - static_cast<float>(_width)) < half)
			{
				const float wGpHalf = el.second.width * lWidth;
				const float raznica = static_cast<float>(_width) - half;

				deltaWidth = raznica / wGpHalf;
			}
			if (el.second.height * lHeight > _height)
			{
				const float hGpHalf = el.second.height * lHeight;
				deltaHeight = _height / hGpHalf;
			}

			el.second.mainSprite->setScale(deltaWidth, deltaHeight);
			el.second.width		*= deltaWidth;
			el.second.height	*= deltaHeight;
		}
	}

}


