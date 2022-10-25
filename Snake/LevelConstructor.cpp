#include "LevelConstructor.h"

using namespace LVLConstructor;

#include<functional>

LVLConstructor::Level::Level(const LVLConfigs& _configs) :
	configs{_configs}
{
	for (unsigned int i = 0; i < configs.width; ++i)
		lvlMAP.push_back(std::vector<LVLblock>(configs.height));
	

	if (configs.autoContr)
	{
		fillFlor(lvlMAP);
		fillWall(lvlMAP, configs.wallPos);
		//fillWater(lvlMAP, configs.waterPos);
	}
	else
	{
		if (checkLvlConfigs(configs))
		{
			for (size_t i = 0; i < lvlMAP.size(); ++i)
				for (size_t j = 0; j < lvlMAP[i].size(); ++j)
					lvlMAP[i][j] = keyToBlock(configs.map[j][i]);
		}
		else
		{
			throw LevelConstructorException(
				__LINE__,
				__FILE__,
				"Check key 'map', 'width' and 'height' for compliance!",
				"Uncorrect lvl properties!");
		}
		
	}
}


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
			
		};
		break;

	case LVLConstructor::AutoConstr::CORNER:
		fillW = [&](lvlmap& _b, unsigned int _i, unsigned int _j)
		{
			
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

const LVLblock LVLConstructor::Level::keyToBlock(const char _blockKey) const
{
	if (_blockKey == LVLPropertiesKeyes::BrickKeyes::flor)
		return LVLblock::FLOR;

	if (_blockKey == LVLPropertiesKeyes::BrickKeyes::wall)
		return LVLblock::WALL;

	if (_blockKey == LVLPropertiesKeyes::BrickKeyes::water)
		return LVLblock::WATER;


	return LVLblock::FLOR;
}

const bool LVLConstructor::Level::checkLvlConfigs(const LVLConfigs& cfg) const
{
	if (configs.height == static_cast<unsigned int>(configs.map.size()))
	{
		for (auto& el : configs.map)
		{
			if (static_cast<unsigned int>(el.size()) != configs.width)
				return false;
		}
	}

	return true;
}

LVLs LVLConstructor::operator++(LVLs& _x)
{
	return _x = static_cast<LVLs>(std::underlying_type<LVLs>::type(_x) + 1);
}



#pragma region LevelConstructorException

// Base lvl constructor exception {
LVLConstructor::Level::LevelConstructorException::LevelConstructorException(
	int _line,
	const char* _file,
	const char* _message,
	const char* _errorString) :
	BaseException(_line, _file),
	message{ _message },
	errorString{_errorString}
{
}
const char* LVLConstructor::Level::LevelConstructorException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl;
	os << "[Error String] " << GetErrorString() << std::endl << std::endl;
	os << "[Message]" << GetMessage() << std::endl << std::endl;

	os << "EXCEPTION IS THROW:" << std::endl;
	os << GetOriginString();
	whatBuffer = os.str();

	return whatBuffer.c_str();
}
const char* LVLConstructor::Level::LevelConstructorException::GetType() const noexcept
{
	return "LVL CONSTRUCTOR EXCEPTION";
}
const std::string LVLConstructor::Level::LevelConstructorException::GetErrorString() const noexcept
{
	return errorString;
}
const std::string LVLConstructor::Level::LevelConstructorException::GetMessage() const noexcept
{
	return message;
}
// Base lvl constructor exception }

#pragma endregion

