#include "ConfigLoader.h"																		
																	
using json = nlohmann::json;

CLoader::Loader::Loader(const std::string& _path) noexcept :
	pathToConf{_path}
{

}

const nlohmann::json CLoader::Loader::getParseFile(const char* _pathToConfig) const
{
	std::ifstream f;
	tryToOpenFile(f, _pathToConfig);

	json file;
	tryToParseFile(file, f, _pathToConfig);

	f.close();
	return file;
}

const std::string CLoader::Loader::getLvlString(LVLConstructor::LVLs _lvl) const
{
	std::string ls = "";

	switch (_lvl)
	{
	case LVLConstructor::LVLs::LVL_1:
		ls = "Lvl1.json";
		break;

	case LVLConstructor::LVLs::LVL_2:
		ls = "Lvl2.json";
		break;

	case LVLConstructor::LVLs::LVL_3:
		ls = "Lvl3.json";
		break;

	case LVLConstructor::LVLs::LVL_4:
		ls = "Lvl4.json";
		break;

	case LVLConstructor::LVLs::LVL_5:
		ls = "Lvl5.json";
		break;

	default:
		break;
	}

	return ls;
}

const void CLoader::Loader::tryToOpenFile(std::ifstream& _iFlofw, const char* _path) const
{
	_iFlofw.open(_path);

	if (!_iFlofw.is_open())
	{
		_iFlofw.close();

		throw CLoader::Loader::LoaderException(
			__LINE__, 
			__FILE__, 
			std::string("No such file or directory: ") + std::string(_path)); 
	}
}
const void CLoader::Loader::tryToParseFile(nlohmann::json& _jFile, std::ifstream& _iFlow, const char* _path) const
{
	try
	{
		_jFile = json::parse(_iFlow);
	}
	catch (json::exception& _ex)
	{
		_iFlow.close();

		throw CLoader::Loader::JsonFileStructCurruptedException(
			__LINE__,
			__FILE__,
			_ex.what(),
			_path);
	}
}

std::shared_ptr<LVLConstructor::Level> CLoader::Loader::GetLVL(LVLConstructor::LVLs _level)
{
	std::string path = CLoader::ConstPaths::pathToLvlvs;
	path += getLvlString(_level);

	json file = getParseFile(path.c_str());
	using namespace LVLConstructor::LVLPropertiesKeyes;


	LVLConstructor::LVLConfigs conf;


	extractValue(file, width.c_str(),		path.c_str(), conf.width);
	extractValue(file, height.c_str(),		path.c_str(), conf.height);
	extractValue(file, startPos.c_str(),	path.c_str(), conf.startPosX, 0);
	extractValue(file, startPos.c_str(),	path.c_str(), conf.startPosY, 1);
	
	extractValue(file, flor.c_str(),		path.c_str(), conf.pathToFlor);
	extractValue(file, wall.c_str(),		path.c_str(), conf.pathToWall);
	extractValue(file, water.c_str(),		path.c_str(), conf.pathToWater);

	
	for (unsigned int i = 0; i < conf.height; ++i)
	{
		std::string temp;
		extractValue(file, map.c_str(), path.c_str(), temp, i);
		conf.map.push_back(temp);
	}
	

	return std::make_shared<LVLConstructor::Level>(conf);
}

const unsigned int CLoader::Loader::GetLvlCount() const
{
	std::ifstream f;
	unsigned int count = 0;

	for (LVLConstructor::LVLs lvl = LVLConstructor::LVLs::LVL_1; lvl < LVLConstructor::LVLs::LVL_MAX; ++lvl)
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

	extractValue(file, CLoader::JsonKeys::apple.c_str(),		 pathToConf.c_str(),		temp.pathToAple);
	extractValue(file, CLoader::JsonKeys::snakeHead.c_str(),	 pathToConf.c_str(),		temp.pathToHead);
	extractValue(file, CLoader::JsonKeys::snakeTorso.c_str(),	 pathToConf.c_str(),		temp.pathToTorso);

	return temp;
}

const CLoader::HudConfigs CLoader::Loader::GetHudPaths(const char* _pathToConfig) const
{
	auto file = getParseFile(pathToConf.c_str());
	HudConfigs temp;

	extractValue(file, CLoader::JsonKeys::windowResolution.c_str(),		pathToConf.c_str(), temp.width,		0);
	extractValue(file, CLoader::JsonKeys::windowResolution.c_str(),		pathToConf.c_str(), temp.height,	1);
	
	extractValue(file, CLoader::JsonKeys::btnPressTexture.c_str(),		pathToConf.c_str(), temp.pathToPressBtn);
	extractValue(file, CLoader::JsonKeys::btnReleaseTexture.c_str(),	pathToConf.c_str(), temp.pathToReleaseBtn);
	extractValue(file, CLoader::JsonKeys::textFont.c_str(),				pathToConf.c_str(), temp.pathToTextFont);
		
	extractValue(file, CLoader::JsonKeys::hudTexture.c_str(),			pathToConf.c_str(), temp.pathToHud);
	extractValue(file, CLoader::JsonKeys::baseWidgetTexture.c_str(),	pathToConf.c_str(), temp.pathToBaseWidget);
	extractValue(file, CLoader::JsonKeys::nameWidgetTexture.c_str(),	pathToConf.c_str(), temp.pathToNameWidget);
		
	return temp;
}

const CLoader::WndConfigs CLoader::Loader::GetWndConfigs(const char* _pathToConfigs) const
{
	auto file = getParseFile(pathToConf.c_str());
	WndConfigs temp;

	extractValue(file, CLoader::JsonKeys::windowResolution.c_str(), pathToConf.c_str(), temp.width, 0);
	extractValue(file, CLoader::JsonKeys::windowResolution.c_str(), pathToConf.c_str(), temp.height, 1);
	
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


#pragma region LoaderExceptions

// File exist exception {
CLoader::Loader::LoaderException::LoaderException(
	int _line,
	const char* _file,
	const std::string& _errorText) :
	BaseException(_line, _file),
	message{ _errorText }
{

}
const char* CLoader::Loader::LoaderException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl;
	os << "[Error String] " << GetErrorString() << std::endl << std::endl;

	os << "EXCEPTION IS THROW:" << std::endl;
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
// File exist exception }

// File parse exception {
CLoader::Loader::JsonParseException::JsonParseException(
	int _line,
	const char* _file,
	const std::string& _errorText,
	const char* _fileName,
	const char* _guilty) :
	LoaderException(_line, _file, _errorText),
	fileName{ _fileName },
	guilty{ _guilty }
{

}
const char* CLoader::Loader::JsonParseException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl;
	os << "[Error String] " << GetErrorString() << std::endl;
	os << "[File name] " << fileName << std::endl;
	os << "[Check the key]: " << guilty << std::endl << std::endl;

	os << "EXCEPTION IS THROW:" << std::endl;
	os << GetOriginString();
	whatBuffer = os.str();

	return whatBuffer.c_str();
}
const char* CLoader::Loader::JsonParseException::GetType() const noexcept
{
	return "FILE PARSE EXCEPTION";
}
const std::string CLoader::Loader::JsonParseException::GetErrorString() const noexcept
{
	return message;
}
// File parse exception }
 
// File struct currupted exception {
CLoader::Loader::JsonFileStructCurruptedException::JsonFileStructCurruptedException(
	int _line,
	const char* _file,
	const std::string& _message,
	const char* _fileName) noexcept :
	LoaderException(_line, _file, _message),
	fileName{ _fileName }
{
}
const char* CLoader::Loader::JsonFileStructCurruptedException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl;
	os << "[Error String] " << GetErrorString() << std::endl;
	os << "[File name] " << fileName << std::endl << std::endl;

	os << "EXCEPTION IS THROW:" << std::endl;
	os << GetOriginString();
	whatBuffer = os.str();

	return whatBuffer.c_str();
}
const char* CLoader::Loader::JsonFileStructCurruptedException::GetType() const noexcept
{
	return "FILE STRUCT CURRUPTED EXCEPTION";
}
const std::string CLoader::Loader::JsonFileStructCurruptedException::GetErrorString() const noexcept
{
	return message;
}
const std::string CLoader::Loader::JsonFileStructCurruptedException::GetFileName() const noexcept
{
	return fileName;
}
// File struct currupted exception }

#pragma endregion


