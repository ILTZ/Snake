#ifndef CONFIGL_H
#define CONFIGL_H

#include <fstream>
#include <string>
#include <unordered_map>


namespace CLoader
{
	enum class ConfigKey
	{
		SNAKE_T = 0,
		SNAKE_H = 1,
		FLOR = 2,
		SHAPE = 3,
		APLE = 4
	};

	class ConfigLoader
	{
	private:
		const std::string pathToConf;
		std::unordered_map<ConfigKey, std::string> pathMap;

	public:
		ConfigLoader(const std::string& _path = ".\\ResourcesConfigs\\Configs.json");

	public:
		ConfigLoader(const ConfigLoader&) = delete;
		ConfigLoader& operator=(const ConfigLoader&) = delete;

	public:
		std::string GetPathTo(ConfigKey _key, const char* _pathToConfig = nullptr);

	private:
		void openFile(std::ifstream& _stream, const char* _newPath);
	};
}
#endif