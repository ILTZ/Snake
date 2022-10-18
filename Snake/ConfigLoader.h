#ifndef CONFIGL_H
#define CONFIGL_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "LevelConstructor.h"

namespace CLoader
{
	namespace ConstData
	{
		const std::string pathToConfigs = ".\\ResourcesConfigs\\Configs.json";
		const std::string pathToLeaders = ".\\ResourcesConfigs\\LeaderBord.json";
	}

	namespace JsonKeys
	{
		const std::string apple				= "APPLE";
		const std::string snakeTorso		= "SNAKE_TORSO";
		const std::string snakeHead			= "SNAKE_HEAD";
		const std::string lvlPath			= "LVL_PATH";
		const std::string windowResolution	= "RESOLUTION";
		const std::string btnPressTexture	= "BTN_PRESS";
		const std::string btnReleaseTexture = "BTN_RELEASE";
		const std::string textFont			= "TEXT_FONT";
		const std::string hudTexture		= "HUD";
		const std::string baseWidgetTexture = "BASE_WIDGET";
		const std::string nameWidgetTexture = "NAME_WIDGET";
		const std::string leader			= "LEADERS";
	}

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
		NAME_WIDGET	= 11,
		LEADERS		= 12,
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

	struct WndConfigs
	{
		unsigned int width = 0u;
		unsigned int height = 0u;
	};

	struct HudConfigs
	{
		unsigned int width	= 0u;
		unsigned int height = 0u;

		std::string pathToPressBtn;
		std::string pathToReleaseBtn;
		std::string pathToTextFont;
		std::string pathToHud;
		std::string pathToBaseWidget;
		std::string pathToNameWidget;
	};

	struct LeadersInfo
	{
		std::string		name;
		unsigned int	points;
	};

	class ConfigLoader
	{
	private:
		const std::string pathToConf;
		mutable std::unordered_map<ConfigKey, std::string> jsonKeys;

	public:
		ConfigLoader(const std::string& _path = ConstData::pathToConfigs);

	public:
		ConfigLoader(const ConfigLoader&)				= delete;
		ConfigLoader& operator=(const ConfigLoader&)	= delete;

	public:
		const std::string GetPathTo(
			ConfigKey _key, 
			const char* _pathToConfig = nullptr) const;
	
		const unsigned int GetLvlCount() const;

	public:
		std::shared_ptr<LVLConstructor::Level> GetLVL(LVLs _level);

	public:
		const SnakePaths GetSnakePaths(const char* _pathToConfig = nullptr)		const;
		const HudConfigs GetHudPaths(const char* _pathToConfig = nullptr)		const;
		const WndConfigs GetWndConfigs(const char* _pathToConfigs = nullptr)	const;
		const std::vector<LeadersInfo> GetLeaders(const char* _pathToFile = nullptr)		const;
		void AddLeaderInLeaderBord(const char* _name, unsigned int _points, const float _time = 0.1);

	private:
		const nlohmann::json getParseFile(const char* _pathToConfig = nullptr)	const;
		void openFile(std::ifstream& _stream, const char* _newPath)				const;

	private:
		const std::string getLvlString(LVLs _lvl) const;

	};
}
#endif