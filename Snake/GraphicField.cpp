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
				sprites[curLvl->GetBlock(i, j)].mainSprite->getGlobalBounds().width		* static_cast<float>(i),
				sprites[curLvl->GetBlock(i, j)].mainSprite->getGlobalBounds().height	* static_cast<float>(j)
			);

			_wnd.draw(*sprites[curLvl->GetBlock(i, j)].mainSprite);
		}
	}
}

void GraphicField::GraphicField::SetScale(const sf::Vector2f& _newScale)
{
	for (auto& el : sprites)
	{
		el.second.mainSprite->setScale(_newScale);
	}
}

void GraphicField::GraphicField::CalculateAndSetScale(const ScaleDeterminant& _det)
{
	for (auto& el : sprites)
	{
		auto newScale = _det.CalculateScale(sf::Vector2f(
			el.second.mainSprite->getGlobalBounds().width,
			el.second.mainSprite->getGlobalBounds().height));
		el.second.mainSprite->setScale(newScale);
	}
}



