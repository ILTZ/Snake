#include "ConfigLoader.h"
#include <nlohmann/json.hpp>

using namespace CLoader;
using json = nlohmann::json;

ConfigLoader::ConfigLoader(const std::string& _path) :
	pathToConf{_path}
{
	jsonKeys[ConfigKey::APLE]		= "APLE";
	jsonKeys[ConfigKey::SNAKE_T]	= "SNAKE_TORSO";
	jsonKeys[ConfigKey::SNAKE_H]	= "SNAKE_HEAD";
	jsonKeys[ConfigKey::LVL_P]		= "LVL_PATH";
	jsonKeys[ConfigKey::RESOLUTION] = "RESOLUTION";
}

void CLoader::ConfigLoader::openFile(std::ifstream& _stream, const char* _newPath) const
{
	if (_newPath)
	{
		_stream.open(_newPath);
		return;
	}
	_stream.open(pathToConf);
}

std::string CLoader::ConfigLoader::getLvlString(LVLs _lvl)
{
	std::string ls = "";

	switch (_lvl)
	{
	case CLoader::LVLs::LVL_1:
		ls = "\\Lvl1.json";
		break;

	case CLoader::LVLs::LVL_2:
		ls = "\\Lvl2.json";
		break;

	case CLoader::LVLs::LVL_3:
		ls = "\\Lvl3.json";
		break;

	case CLoader::LVLs::LVL_4:
		ls = "\\Lvl4.json";
		break;

	case CLoader::LVLs::LVL_5:
		ls = "\\Lvl5.json";
		break;

	default:
		break;
	}

	return ls;
}

std::string ConfigLoader::GetPathTo(ConfigKey _key, const char* _pathToConfig)
{
	assert(_key != ConfigKey::RESOLUTION);

	std::ifstream f;
	openFile(f, _pathToConfig);

	json file = json::parse(f);
	f.close();

	return file[jsonKeys[_key]];
}

std::shared_ptr<LVLConstructor::Level> CLoader::ConfigLoader::GetLVL(LVLs _level)
{
	auto path = GetPathTo(ConfigKey::LVL_P);
	path += getLvlString(_level);

	std::ifstream f;
	openFile(f, path.c_str());
	json file = json::parse(f);


	// Read configs from .json file {

	LVLConstructor::LVLConfigs conf;

	if (file["mode"] == "hand")
		conf.autoContr = false;
	else
		conf.autoContr = true;

	conf.width			= file["width"];
	conf.height			= file["height"];
	conf.startPosX		= file["startPos"][0];
	conf.startPosY		= file["startPos"][1];

	conf.pathToFlor		= file["florPath"];
	conf.pathToWall		= file["wallPath"];
	conf.pathToWater	= file["waterPath"];

	auto getAuto = [&](const std::string& _mode)
	{
		if (_mode == "none")
			return LVLConstructor::AutoConstr::NONE;

		if (_mode == "edges")
			return LVLConstructor::AutoConstr::EDGES;

		if (_mode == "corner")
			return LVLConstructor::AutoConstr::CORNER;

		if (_mode == "discret")
			return LVLConstructor::AutoConstr::DISCRET;

		return LVLConstructor::AutoConstr::NONE;
	};

	conf.wallPos = getAuto(file["wallPos"]);
	conf.waterPos = getAuto(file["waterPos"]);

	// Read configs from .json file }

	return std::make_shared<LVLConstructor::Level>(conf);
}

unsigned int CLoader::ConfigLoader::GetLvlCount()
{
	unsigned int count = 0;
	std::ifstream f;

	for (LVLs lvl = LVLs::LVL_1; lvl < LVLs::LVL_MAX; ++lvl)
	{
		auto path = GetPathTo(ConfigKey::LVL_P);
		path += getLvlString(lvl);

		openFile(f, path.c_str());

		if (f.good())
			++count;

		f.close();
	}
	

	return count;
}

const std::pair<unsigned int, unsigned int> CLoader::ConfigLoader::GetResolution(const char* _pathToConfig)
{
	std::ifstream f;
	openFile(f, _pathToConfig);

	json file = json::parse(f);
	f.close();

	return std::make_pair<unsigned int, unsigned int>
		(file[jsonKeys[ConfigKey::RESOLUTION]][0], file[jsonKeys[ConfigKey::RESOLUTION]][1]);
}

LVLs CLoader::operator++(LVLs& _x)
{
	return _x = static_cast<LVLs>(std::underlying_type<LVLs>::type(_x) + 1);
}
