#include "ConfigLoader.h"
#include <nlohmann/json.hpp>

using namespace CLoader;
using json = nlohmann::json;

ConfigLoader::ConfigLoader(const std::string& _path) :
	pathToConf{_path}
{
	pathMap[ConfigKey::APLE]	= "APLE";
	pathMap[ConfigKey::SNAKE_T] = "SNAKE_TORSO";
	pathMap[ConfigKey::SNAKE_H] = "SNAKE_HEAD";
	pathMap[ConfigKey::FLOR]	= "FLOR";
	pathMap[ConfigKey::SHAPE]	= "SHAPE";

}

void CLoader::ConfigLoader::openFile(std::ifstream& _stream, const char* _newPath)
{
	if (_newPath)
	{
		_stream.open(_newPath);
		return;
	}
	_stream.open(pathToConf);
}

std::string ConfigLoader::GetPathTo(ConfigKey _key, const char* _pathToConfig)
{
	std::ifstream f;
	openFile(f, _pathToConfig);

	json file = json::parse(f);

	return file[pathMap[_key]];
}
