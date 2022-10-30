#ifndef CONFIGL_H
#define CONFIGL_H

#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "LevelConstructor.h"
#include "BaseException.h"

namespace CLoader
{
	namespace ConstPaths
	{
		const std::string pathToConfigs = ".\\ResourcesConfigs\\Configs.json";
		const std::string pathToLeaders = ".\\ResourcesConfigs\\LeaderBord.json";
		const std::string pathToLvlvs	= ".\\ResourcesConfigs\\LVLs\\";
	}

	namespace JsonKeys
	{
		const std::string lvlPath			= "LVL_PATH";
		const std::string windowResolution	= "RESOLUTION";
		const std::string btnPressTexture	= "BTN_PRESS";
		const std::string btnReleaseTexture = "BTN_RELEASE";
		const std::string textFont			= "TEXT_FONT";
		const std::string hudTexture		= "HUD";
		const std::string baseWidgetTexture = "BASE_WIDGET";
		const std::string nameWidgetTexture = "NAME_WIDGET";
		const std::string leader			= "LEADERS";
		const std::string title				= "TITLE";
		const std::string bckground			= "BACKGROUND";
		const std::string icon				= "ICON";
	}

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

		std::string title;
		std::string pathToFont;
		std::string pathToBackgound;
		std::string pathToIcon;
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
		LeadersInfo(
			const std::string& _name, 
			unsigned int _points, 
			unsigned int _minuts, 
			unsigned int _seconds);

		LeadersInfo(const char* _error);

		std::string		name;
		unsigned int	points;

		unsigned int	minuts;
		unsigned int	seconds;

		const std::string TimeToString() const;
	};

	class Loader
	{
	public:
		class LoaderException : public BaseException
		{
		protected:
			const std::string	message;

		public:
			LoaderException(
				int _line, 
				const char* _file, 
				const std::string& _errorText);

		public:
			const char* what()				const noexcept override;
			const char* GetType()			const noexcept override;

			const std::string GetErrorString()	const noexcept;

		};

		class JsonParseException : public LoaderException
		{
		private:
			const std::string fileName;
			const std::string guilty;

		public:
			JsonParseException(
				int _line,
				const char* _file,
				const std::string& _errorText,
				const char* _fileName,
				const char* _guilty);

		public:
			const char* what()				const noexcept override;
			const char* GetType()			const noexcept override;

			const std::string GetErrorString()	const noexcept;
		};

		class JsonFileStructCurruptedException : public LoaderException
		{
		private:
			const std::string fileName;

		public:
			JsonFileStructCurruptedException(
				int _line,
				const char* _file,
				const std::string& _message,
				const char* _fileName) noexcept;

		public:
			const char* what()				const noexcept override;
			const char* GetType()			const noexcept override;

			const std::string GetErrorString()	const noexcept;
			const std::string GetFileName()		const noexcept;
		};

	private:
		const std::string pathToConf;

	public:
		Loader(const std::string& _path = ConstPaths::pathToConfigs) noexcept;

	public:
		Loader(const Loader&)				= delete;
		Loader& operator=(const Loader&)	= delete;

	public:
		const unsigned int GetLvlCount() const;

	public:
		std::shared_ptr<LVLConstructor::Level> GetLVL(LVLConstructor::LVLs _level);

	public:
		const SnakePaths GetSnakePaths(LVLConstructor::LVLs _level)							const;
		const HudConfigs GetHudPaths(const char* _pathToConfig = nullptr)					const;
		const WndConfigs GetWndConfigs(const char* _pathToConfigs = nullptr)				const;
		const std::vector<LeadersInfo> GetLeaders(const char* _pathToFile = nullptr)		const;
		void AddLeaderInLeaderBord(
			const char* _name, 
			unsigned int _points, 
			unsigned int _minuts, 
			unsigned int _seconds);

	private:
		const nlohmann::json getParseFile(const char* _pathToConfig = nullptr)	const;
		
	private:
		const std::string getLvlString(LVLConstructor::LVLs _lvl) const;

	private:
		template <typename T>
		const void extractValue(
			const nlohmann::json& _file,
			const char* _key,
			const char* _path,
			T& _value, 
			int _index = -1) const;

	private:
		const void tryToOpenFile(
			std::ifstream& _iFlofw, 
			const char* _path) const;

		const void tryToParseFile(
			nlohmann::json& _jFile, 
			std::ifstream& _iFlow, 
			const char* _path) const;

	};

	template<typename T>
	inline const void Loader::extractValue( 
		const nlohmann::json& _file, 
		const char* _key, 
		const char* _path,
		T& _value,
		int _index) const
	{
		try
		{
			if (_file.find(_key) == _file.end())
				throw std::exception("There is no such key in the file (or the key is written incorrectly).");

			if (_index >= 0) // when we try to extract value from array
			{
				if (_file[_key].is_array())
				{
					if (_file[_key].size() > _index)
					{
						_value = static_cast<T>(_file[_key][_index]);
					}
					else
					{
						throw std::exception(
							(std::string("No index [") + 
								std::to_string(_index) + 
								std::string("] in array"))
							.c_str());
					}
				}
				else
				{
					throw std::exception("An array is assumed, but it is not!");
				}

			}
			else
				_value = static_cast<T>(_file[_key]);

		}
		catch (std::exception& _ex)
		{
			throw CLoader::Loader::JsonParseException(
				__LINE__,
				__FILE__,
				std::string(_ex.what()),
				_path,
				_key);
		}
	}


	
}

#endif