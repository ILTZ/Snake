#include "LevelConstructor.h"

using namespace LVLConstructor;

#include<functional>

LVLConstructor::Level::Level(const LVLConfigs& _configs) :
	configs{_configs}
{
	for (unsigned int i = 0; i < configs.width; ++i)
	{
		lvlMAP.push_back(std::vector<LVLblock>(configs.height));
	}

	if (configs.autoContr)
	{
		fillFlor(lvlMAP);
		fillWall(lvlMAP, configs.wallPos);
		fillWater(lvlMAP, configs.waterPos);
		setStartPos(lvlMAP, configs.startPosX, configs.startPosY);
	}
}

// Get() {

const LVLConfigs& LVLConstructor::Level::GetConfigs() const
{
	return configs;
}

const LVLblock& LVLConstructor::Level::GetBlock(int _x, int _y) const
{
	return lvlMAP[_x][_y];
}

const lvlmap& LVLConstructor::Level::GetLvlMap() const
{
	return lvlMAP;
}

// Get() }


void LVLConstructor::Level::fillFlor(lvlmap& _vec)
{
	for (unsigned int i = 0; i < configs.width; ++i)
	{
		for (unsigned int j = 0; j < configs.height; ++j)
		{
			_vec[i][j] = LVLblock::FLOR;
		}
	}
}

void LVLConstructor::Level::fillWall(lvlmap& _vec, AutoConstr _wallPos)
{
	if (_wallPos == AutoConstr::NONE)
		return;

	std::function<void(LVLblock& _b, unsigned int _i, unsigned int _j)> fillF;


	switch (_wallPos)
	{
	case LVLConstructor::AutoConstr::EDGES:
		fillF = [&](LVLblock& _b, unsigned int _i, unsigned int _j)
		{
			{
				if ((_i == 0 || _i == configs.width - 1)
					||
					(_j == 0 || _j == configs.height - 1))
				{
					_b = LVLblock::WALL;
				}
			}
		};
		break;

	case LVLConstructor::AutoConstr::CORNER:
		fillF = [&](LVLblock& _b, unsigned int _i, unsigned int _j)
		{
			if ((_i < configs.width / 3 || _i >(configs.width / 3 * 2))
				&&
				(_j < configs.height / 3 || _j >(configs.height / 3 * 2)))
			{
				_b = LVLblock::WALL;
			}
		};
		break;

	case LVLConstructor::AutoConstr::DISCRET:
		fillF = [&](LVLblock& _b, unsigned int _i, unsigned int _j)
		{
			
		};
		break;

	default:
		break;
	}


	for (unsigned int i = 0; i < configs.width; ++i)
	{
		for (unsigned int j = 0; j < configs.height; ++j)
		{
			fillF(_vec[i][j], i, j);
		}
	}
}

void LVLConstructor::Level::fillWater(lvlmap& _vec, AutoConstr _waterPos)
{
	if (_waterPos == AutoConstr::NONE)
		return;

	std::function<void(lvlmap& _b, unsigned int _i, unsigned int _j)> fillW;

	switch (_waterPos)
	{
	case LVLConstructor::AutoConstr::EDGES:
		fillW = [&](lvlmap& _b, unsigned int _i, unsigned int _j)
		{
			if (_b[_i][_j] != LVLblock::WALL)
			{
				if ((_i == 0 || _i == configs.width - 1)
					||
					(_j == 0 || _j == configs.height - 1))
				{
					_b[_i][_j] = LVLblock::WATER;
				}
			}
			else 
			{
				if ((_i == 1 || _i == configs.width - 2)
					||
					(_j == 1 || _j == configs.height - 2))
				{
					_b[_i][_j] = LVLblock::WATER;
				}
			}
		};
		break;

	case LVLConstructor::AutoConstr::CORNER:
		fillW = [&](lvlmap& _b, unsigned int _i, unsigned int _j)
		{
			if (_b[_i][_j] != LVLblock::WALL)
			{
				if ((_i < configs.width / 3 || _i >(configs.width / 3 * 2))
					&&
					(_j < configs.height / 3 || _j >(configs.height / 3 * 2)))
				{
					_b[_i][_j] = LVLblock::WATER;
				}
			}
			else
			{
				if ((_i < configs.width / 3 || _i >(configs.width / 3 * 2))
					&&
					(_j < configs.height / 3 || _j >(configs.height / 3 * 2)))
				{
					//_b[_i + 1][_j + 1] = LVLblock::WATER;
				}
			}
		};
		break;

	case LVLConstructor::AutoConstr::DISCRET:
		fillW = [&](lvlmap& _b, unsigned int _i, unsigned int _j)
		{

		};
		break;

	default:
		break;
	}

	for (unsigned int i = 0; i < configs.width; ++i)
	{
		for (unsigned int j = 0; j < configs.height; ++j)
		{
			fillW(_vec, i, j);
		}
	}
}

void LVLConstructor::Level::setStartPos(lvlmap& _vec, int _xPos, int _yPos)
{
}
