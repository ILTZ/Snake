#ifndef CONFIGL_H
#define CONFIGL_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "LevelConstructor.h"

namespace CLoader
{
	enum class ConfigKey
	{
		SNAKE_T		= 0,
		SNAKE_H		= 1,
		APLE		= 3,
		LVL_P		= 4,
		RESOLUTION	= 5,
		BTN_PRESS	= 6,
		BTN_RELEASE = 7,
		TEXT_FONT	= 8,
		HUD			= 9,
		BASE_WIDGET = 10,
	};

	enum class LVLs
	{
		LVL_1 = 0,
		LVL_2 = 1,
		LVL_3 = 2,
		LVL_4 = 3,
		LVL_5 = 4,

		LVL_MAX = 5
	};
	LVLs operator++(LVLs& _x);


	struct SnakePaths
	{
		std::string pathToHead;
		std::string pathToTorso;
		std::string pathToAple;
	};

	struct HudConfigs
	{
		unsigned int width;
		unsigned int height;

		std::string pathToPressBtn;
		std::string pathToReleaseBtn;
		std::string pathToTextFont;
		std::string pathToHud;
		std::string pathToBaseWidget;
	};

	class ConfigLoader
	{
	private:
		const std::string pathToConf;
		std::unordered_map<ConfigKey, std::string> jsonKeys;

	public:
		ConfigLoader(const std::string& _path = ".\\ResourcesConfigs\\Configs.json");

	public:
		ConfigLoader(const ConfigLoader&) = delete;
		ConfigLoader& operator=(const ConfigLoader&) = delete;

	public:
		std::string GetPathTo(ConfigKey _key, const char* _pathToConfig = nullptr);
		std::shared_ptr<LVLConstructor::Level> GetLVL(LVLs _level);
		unsigned int GetLvlCount();

	public:
		SnakePaths GetSnakeProp(const char* _pathToConfig = nullptr);
		HudConfigs GetHudConfigs(const char* _pathToConfig = nullptr);

	private:
		nlohmann::json getParseFile(const char* _pathToConfig = nullptr);
		void openFile(std::ifstream& _stream, const char* _newPath) const;

	private:
		std::string getLvlString(LVLs _lvl);
	};
}
#endif