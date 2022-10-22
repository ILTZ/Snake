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

#define TRY_OPEN_FILE_EXCEPTION(streamFlow, path)							\
{																			\
	if (streamFlow.bad())													\
	{																		\
		streamFlow.close();													\
		throw Loader::LoaderException(										\
			__LINE__,														\
			__FILE__,														\
			std::string("No such file or directory:") + std::string(path)); \
	}																		\
																			\
}																			\

#define THROW_JSON_PARSE_EXCEPTION(path)									\
{																			\
	throw Loader::LoaderException(											\
		__LINE__,															\
		__FILE__,															\
			std::string("File currupted:") + std::string(path));			\																\
}																			\



#include "ConfigLoader.h"

#include <sstream>
#include <exception>

//using namespace CLoader;
using json = nlohmann::json;

CLoader::Loader::Loader(const std::string& _path) :
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

const nlohmann::json CLoader::Loader::getParseFile(const char* _pathToConfig) const
{
	std::ifstream f;
	openFile(f, _pathToConfig);

	json file = json::parse(f);
	f.close();

	return file;
}



void CLoader::Loader::openFile(std::ifstream& _stream, const char* _newPath) const
{
	const char* tempP = nullptr;

	if (_newPath)
		tempP = _newPath;
	else
		tempP = pathToConf.c_str();
	
	_stream.open(tempP);
	
	TRY_OPEN_FILE_EXCEPTION(_stream, tempP);
}

const std::string CLoader::Loader::getLvlString(LVLs _lvl) const
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



std::shared_ptr<LVLConstructor::Level> CLoader::Loader::GetLVL(LVLs _level)
{
	std::string path = getParseFile(
		pathToConf.c_str())[jsonKeys[ConfigKey::LVL_P]];
	path += getLvlString(_level);

	json file = getParseFile(path.c_str());


	LVLConstructor::LVLConfigs conf;

	if (file[mode] == "hand")
		conf.autoContr = false;
	else
		conf.autoContr = true;

	conf.width			= file[width];
	conf.height			= file[height];
	conf.startPosX		= file[startPos][0];
	conf.startPosY		= file[startPos][1];

	conf.pathToFlor		= file[flor];
	conf.pathToWall		= file[wall];
	conf.pathToWater	= file[water];

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


	return std::make_shared<LVLConstructor::Level>(conf);
}

const unsigned int CLoader::Loader::GetLvlCount() const
{
	std::string path = getParseFile(
		pathToConf.c_str())[jsonKeys[ConfigKey::LVL_P]];

	std::ifstream f;
	unsigned int count = 0;

	for (LVLs lvl = LVLs::LVL_1; lvl < LVLs::LVL_MAX; ++lvl)
	{
		try
		{
			openFile(f, (path + getLvlString(lvl)).c_str());
			if (f.good())
				++count;
			f.close();
		}
		catch (CLoader::Loader::LoaderException&) {}
			
		f.close();		
	}
	
	return count;
}

const CLoader::SnakePaths CLoader::Loader::GetSnakePaths(const char* _pathToConfig) const
{
	auto file = getParseFile(_pathToConfig);
	SnakePaths temp;

	temp.pathToAple = file[jsonKeys[ConfigKey::APLE]];
	temp.pathToHead = file[jsonKeys[ConfigKey::SNAKE_H]];
	temp.pathToTorso = file[jsonKeys[ConfigKey::SNAKE_T]];

	return temp;
}

const CLoader::HudConfigs CLoader::Loader::GetHudPaths(const char* _pathToConfig) const
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

const CLoader::WndConfigs CLoader::Loader::GetWndConfigs(const char* _pathToConfigs) const
{
	auto file = getParseFile(_pathToConfigs);
	WndConfigs temp;

	temp.width = file[jsonKeys[ConfigKey::RESOLUTION]][0];
	temp.height = file[jsonKeys[ConfigKey::RESOLUTION]][1];
	
	return temp;
}

const std::vector<CLoader::LeadersInfo> CLoader::Loader::GetLeaders(const char* _pathToFile) const
{
	std::vector<LeadersInfo> leaders;

	auto arr = getParseFile(ConstPaths::pathToLeaders.c_str());

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

void CLoader::Loader::AddLeaderInLeaderBord(
	const char* _name,
	unsigned int _points,
	unsigned int _minuts,
	unsigned int _seconds)
{
	auto leadersFile = getParseFile(ConstPaths::pathToLeaders.c_str());
	

	auto found = leadersFile.find(_name);
	if (found != leadersFile.end())
	{
		if(static_cast<unsigned int>(found.value()[0]) < _points)
		{
			leadersFile[_name] = { _points, _minuts, _seconds };	
		}
	}
	else
	{
		leadersFile[_name] = { _points, _minuts, _seconds };
	}


	std::ofstream file(ConstPaths::pathToLeaders.c_str());

	if (file.is_open())
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


CLoader::LVLs CLoader::operator++(LVLs& _x)
{
	return _x = static_cast<LVLs>(std::underlying_type<LVLs>::type(_x) + 1);
}



// Exception {
CLoader::Loader::LoaderException::LoaderException(
	int _line,
	const char* _file,
	const std::string& _errorText,
	bool _toAbort) :
	BaseException(_line, _file),
	message{_errorText},
	aborted{_toAbort}
{

}
const char* CLoader::Loader::LoaderException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl
		<< "[Error String] " << GetErrorString() << std::endl;

	os << GetOriginString();
	whatBuffer = os.str();

	return whatBuffer.c_str();
}
const char* CLoader::Loader::LoaderException::GetType() const noexcept
{
	return "Loader exception";
}
const bool CLoader::Loader::LoaderException::IsAbort() const noexcept
{
	return aborted;
}
const std::string CLoader::Loader::LoaderException::GetErrorString() const noexcept
{
	return message;
}
// Exception }