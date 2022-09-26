#include "ConfigLoader.h"


using namespace CLoader;
using json = nlohmann::json;

ConfigLoader::ConfigLoader(const std::string& _path) :
	pathToConf{_path}
{
	jsonKeys[ConfigKey::APLE]			= "APLE";
	jsonKeys[ConfigKey::SNAKE_T]		= "SNAKE_TORSO";
	jsonKeys[ConfigKey::SNAKE_H]		= "SNAKE_HEAD";
	jsonKeys[ConfigKey::LVL_P]			= "LVL_PATH";
	jsonKeys[ConfigKey::RESOLUTION]		= "RESOLUTION";
	jsonKeys[ConfigKey::BTN_PRESS]		= "BTN_PRESS";
	jsonKeys[ConfigKey::BTN_RELEASE]	= "BTN_RELEASE";
	jsonKeys[ConfigKey::TEXT_FONT]		= "TEXT_FONT";
	jsonKeys[ConfigKey::HUD]			= "HUD";
}

nlohmann::json CLoader::ConfigLoader::getParseFile(const char* _pathToConfig)
{
	std::ifstream f;
	openFile(f, _pathToConfig);

	json file = json::parse(f);
	f.close();

	return file;
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

SnakePaths CLoader::ConfigLoader::GetSnakeProp(const char* _pathToConfig)
{
	auto file = getParseFile(_pathToConfig);

	SnakePaths temp;

	temp.pathToAple = file[jsonKeys[ConfigKey::APLE]];
	temp.pathToHead = file[jsonKeys[ConfigKey::SNAKE_H]];
	temp.pathToTorso = file[jsonKeys[ConfigKey::SNAKE_T]];

	return temp;
}

HudConfigs CLoader::ConfigLoader::GetHudConfigs(const char* _pathToConfig)
{
	auto file = getParseFile(_pathToConfig);

	HudConfigs temp;

	temp.width = file[jsonKeys[ConfigKey::RESOLUTION]][0];
	temp.height = file[jsonKeys[ConfigKey::RESOLUTION]][1];

	temp.pathToPressBtn = file[jsonKeys[ConfigKey::BTN_PRESS]];
	temp.pathToReleaseBtn = file[jsonKeys[ConfigKey::BTN_RELEASE]];
	temp.pathToTextFont = file[jsonKeys[ConfigKey::TEXT_FONT]];
	temp.pathToHud = file[jsonKeys[ConfigKey::HUD]];

	return temp;
}

LVLs CLoader::operator++(LVLs& _x)
{
	return _x = static_cast<LVLs>(std::underlying_type<LVLs>::type(_x) + 1);
}
