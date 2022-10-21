#ifndef NDEBUG

#include <iostream>

#define JSON_TRY_USER if (true)
#define JSON_CATCH_USER(exception) if(false)
#define JSON_THROW_USER(exception)                           \
    {std::clog << "Error in " << __FILE__ << ":" << __LINE__ \
               << " (function " << __FUNCTION__ << ") - "    \
               << (exception).what() << std::endl;			 \
				throw exception;}

#endif // !NDEBUG

#include "ConfigLoader.h"

#include <sstream>
#include <exception>

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
	jsonKeys[ConfigKey::BASE_WIDGET]	= "BASE_WIDGET";
	jsonKeys[ConfigKey::NAME_WIDGET]	= "NAME_WIDGET";
}

const nlohmann::json CLoader::ConfigLoader::getParseFile(const char* _pathToConfig) const
{
	std::ifstream f;
	openFile(f, _pathToConfig);

	if (f.bad())
		throw std::exception("No such file or directory");

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

const std::string CLoader::ConfigLoader::getLvlString(LVLs _lvl) const
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

const std::string ConfigLoader::GetPathTo(ConfigKey _key, const char* _pathToConfig) const
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

const unsigned int CLoader::ConfigLoader::GetLvlCount() const
{
	unsigned int count = 0;
	std::ifstream f;

	auto path = GetPathTo(ConfigKey::LVL_P);

	for (LVLs lvl = LVLs::LVL_1; lvl < LVLs::LVL_MAX; ++lvl)
	{
		openFile(f, (path + getLvlString(lvl)).c_str());
		if (f.good())
			++count;

		f.close();
	}
	

	return count;
}

const SnakePaths CLoader::ConfigLoader::GetSnakePaths(const char* _pathToConfig) const 
{
	auto file = getParseFile(_pathToConfig);
	SnakePaths temp;

	temp.pathToAple = file[jsonKeys[ConfigKey::APLE]];
	temp.pathToHead = file[jsonKeys[ConfigKey::SNAKE_H]];
	temp.pathToTorso = file[jsonKeys[ConfigKey::SNAKE_T]];

	return temp;
}

const HudConfigs CLoader::ConfigLoader::GetHudPaths(const char* _pathToConfig) const
{
	auto file = getParseFile(_pathToConfig);
	HudConfigs temp;

	temp.width					= file[jsonKeys[ConfigKey::RESOLUTION]][0];
	temp.height					= file[jsonKeys[ConfigKey::RESOLUTION]][1];

	temp.pathToPressBtn			= file[jsonKeys[ConfigKey::BTN_PRESS]];
	temp.pathToReleaseBtn		= file[jsonKeys[ConfigKey::BTN_RELEASE]];
	temp.pathToTextFont			= file[jsonKeys[ConfigKey::TEXT_FONT]];
	temp.pathToHud				= file[jsonKeys[ConfigKey::HUD]];
	temp.pathToBaseWidget		= file[jsonKeys[ConfigKey::BASE_WIDGET]];
	temp.pathToNameWidget		= file[jsonKeys[ConfigKey::NAME_WIDGET]];

	return temp;
}

const WndConfigs CLoader::ConfigLoader::GetWndConfigs(const char* _pathToConfigs) const
{
	auto file = getParseFile(_pathToConfigs);
	WndConfigs temp;

	temp.width = file[jsonKeys[ConfigKey::RESOLUTION]][0];
	temp.height = file[jsonKeys[ConfigKey::RESOLUTION]][1];
	
	return temp;
}

const std::vector<LeadersInfo> CLoader::ConfigLoader::GetLeaders(const char* _pathToFile) const
{
	std::vector<LeadersInfo> leaders;

	auto arr = getParseFile(ConstData::pathToLeaders.c_str())[JsonKeys::leader];

	for (json::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		try
		{
			leaders.emplace_back(
				it.key(), 
				static_cast<unsigned int>(it.value()[0]),
				static_cast<unsigned int>(it.value()[1]),
				static_cast<unsigned int>(it.value()[2]));
		}
		catch (std::exception&)
		{
			leaders.emplace_back("Record is broken");
		}
	}
	
	return leaders;
}

void CLoader::ConfigLoader::AddLeaderInLeaderBord(
	const char* _name,
	unsigned int _points,
	unsigned int _minuts,
	unsigned int _seconds)
{
	auto leadersFile = getParseFile(ConstData::pathToLeaders.c_str());
	leadersFile[JsonKeys::leader][_name] = { _points, _minuts, _seconds };

	std::ofstream file(ConstData::pathToLeaders.c_str());
	file << leadersFile;
	file.close();
}

CLoader::LeadersInfo::LeadersInfo(
	const std::string& _name,
	unsigned int _points,
	unsigned int _minuts,
	unsigned int _seconds) :
	name{_name}, 
	points{_points}, 
	minuts{_minuts}, 
	seconds{_seconds}
{

}

CLoader::LeadersInfo::LeadersInfo(const char* _error) :
	name{ _error },
	points{ 0u },
	minuts{ 0u },
	seconds{ 0u }
{

}

const std::string CLoader::LeadersInfo::TimeToString() const
{
	std::ostringstream ss;

	if (minuts < 10u)
		ss << 0u;
	ss << minuts;

	ss << ':';

	if (seconds < 10u)
		ss << 0u;
	ss << seconds;

	return ss.str();
}


LVLs CLoader::operator++(LVLs& _x)
{
	return _x = static_cast<LVLs>(std::underlying_type<LVLs>::type(_x) + 1);
}
