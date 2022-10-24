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

#define TRY_OPEN_FILE_EXCEPTION(streamFlow, path)							\
{																			\
	if (streamFlow.bad())													\
	{																		\
		streamFlow.close();													\
		throw CLoader::Loader::LoaderException(								\
			__LINE__,														\
			__FILE__,														\
			std::string("No such file or directory: ") + std::string(path));\
	}																		\
																			\
}																			\

#define THROW_PARSE_EXCEPTION(path)								\
{																\
	throw CLoader::Loader::LoaderException(						\
		__LINE__,												\
		__FILE__,												\
		std::string("File currapted: ") + std::string(path));	\
}																\




#include <sstream>
#include <exception>

//using namespace CLoader;
using json = nlohmann::json;

CLoader::Loader::Loader(const std::string& _path) :
	pathToConf{_path}
{
	/*jsonKeys[ConfigKey::APLE]			= "APLE";
	jsonKeys[ConfigKey::SNAKE_T]		= "SNAKE_TORSO";
	jsonKeys[ConfigKey::SNAKE_H]		= "SNAKE_HEAD";
	jsonKeys[ConfigKey::LVL_P]			= "LVL_PATH";
	jsonKeys[ConfigKey::RESOLUTION]		= "RESOLUTION";
	jsonKeys[ConfigKey::BTN_PRESS]		= "BTN_PRESS";
	jsonKeys[ConfigKey::BTN_RELEASE]	= "BTN_RELEASE";
	jsonKeys[ConfigKey::TEXT_FONT]		= "TEXT_FONT";
	jsonKeys[ConfigKey::HUD]			= "HUD";
	jsonKeys[ConfigKey::BASE_WIDGET]	= "BASE_WIDGET";
	jsonKeys[ConfigKey::NAME_WIDGET]	= "NAME_WIDGET";*/
}

const nlohmann::json CLoader::Loader::getParseFile(const char* _pathToConfig) const
{
	std::ifstream f;
	f.open(_pathToConfig);

	TRY_OPEN_FILE_EXCEPTION(f, _pathToConfig);

	json file = json::parse(f);
	f.close();

	return file;
}

const std::string CLoader::Loader::getLvlString(LVLs _lvl) const
{
	std::string ls = "";

	switch (_lvl)
	{
	case CLoader::LVLs::LVL_1:
		ls = "Lvl1.json";
		break;

	case CLoader::LVLs::LVL_2:
		ls = "Lvl2.json";
		break;

	case CLoader::LVLs::LVL_3:
		ls = "Lvl3.json";
		break;

	case CLoader::LVLs::LVL_4:
		ls = "Lvl4.json";
		break;

	case CLoader::LVLs::LVL_5:
		ls = "Lvl5.json";
		break;

	default:
		break;
	}

	return ls;
}



std::shared_ptr<LVLConstructor::Level> CLoader::Loader::GetLVL(LVLs _level)
{
	std::string path = CLoader::ConstPaths::pathToLvlvs;
	path += getLvlString(_level);

	json file = getParseFile(path.c_str());
	LVLConstructor::LVLConfigs conf;


	try
	{
		using namespace LVLConstructor::LVLPropertiesKeyes;

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

		conf.wallPos	= getAuto(file["wallPos"]);
		conf.waterPos	= getAuto(file["waterPos"]);
	}
	catch (std::exception&)
	{
		THROW_PARSE_EXCEPTION(path);
	}

	return std::make_shared<LVLConstructor::Level>(conf);
}

const unsigned int CLoader::Loader::GetLvlCount() const
{
	std::ifstream f;
	unsigned int count = 0;

	for (LVLs lvl = LVLs::LVL_1; lvl < LVLs::LVL_MAX; ++lvl)
	{
		f.open(CLoader::ConstPaths::pathToLvlvs + getLvlString(lvl));
		if (f.good())
			++count;
		f.close();	
	}
	
	return count;
}

const CLoader::SnakePaths CLoader::Loader::GetSnakePaths(const char* _pathToConfig) const
{
	auto file = getParseFile(pathToConf.c_str());
	SnakePaths temp;

	try
	{
		temp.pathToAple		= file[CLoader::JsonKeys::apple];
		temp.pathToHead		= file[CLoader::JsonKeys::snakeHead];
		temp.pathToTorso	= file[CLoader::JsonKeys::snakeTorso];
	}
	catch (json::exception&)
	{
		THROW_PARSE_EXCEPTION(pathToConf.c_str());
	}

	return temp;
}

const CLoader::HudConfigs CLoader::Loader::GetHudPaths(const char* _pathToConfig) const
{
	auto file = getParseFile(pathToConf.c_str());
	HudConfigs temp;

	try
	{
		temp.width				= file[CLoader::JsonKeys::windowResolution][0];
		temp.height				= file[CLoader::JsonKeys::windowResolution][1];

		temp.pathToPressBtn		= file[CLoader::JsonKeys::btnPressTexture];
		temp.pathToReleaseBtn	= file[CLoader::JsonKeys::btnReleaseTexture];
		temp.pathToTextFont		= file[CLoader::JsonKeys::textFont];
		temp.pathToHud			= file[CLoader::JsonKeys::hudTexture];
		temp.pathToBaseWidget	= file[CLoader::JsonKeys::baseWidgetTexture];
		temp.pathToNameWidget	= file[CLoader::JsonKeys::nameWidgetTexture];
	}
	catch (json::exception&)
	{
		THROW_PARSE_EXCEPTION(pathToConf.c_str());
	}

	return temp;
}

const CLoader::WndConfigs CLoader::Loader::GetWndConfigs(const char* _pathToConfigs) const
{
	auto file = getParseFile(pathToConf.c_str());
	WndConfigs temp;

	try
	{
		temp.width		= file[CLoader::JsonKeys::windowResolution][0];
		temp.height		= file[CLoader::JsonKeys::windowResolution][1];
	}
	catch (json::exception&)
	{
		THROW_PARSE_EXCEPTION(pathToConf.c_str());
	}

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
	const std::string& _errorText) :
	BaseException(_line, _file),
	message{_errorText}
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
const std::string CLoader::Loader::LoaderException::GetErrorString() const noexcept
{
	return message;
}
// Exception }