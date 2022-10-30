#ifndef LVLCONSTR_H
#define LVLCONSTR_H

#include <string>
#include <vector>

#include "BaseException.h"

namespace LVLConstructor
{
	enum class LVLblock
	{
		FLOR	= 0,
		WALL	= 1,
		WATER	= 2,
		SNAKE_H = 3,
		SNAKE_T	= 4
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

	namespace LVLPropertiesKeyes
	{
		const std::string width		= "WIDTH";
		const std::string height	= "HEIGHT";
		const std::string startPos	= "START_POS";

		const std::string flor		= "FLOR_PATH";
		const std::string water		= "WATER_PATH";
		const std::string wall		= "WALL_PATH";

		const std::string map		= "MAP";
		
		const std::string apple			= "APPLE";
		const std::string snakeTorso	= "SNAKE_TORSO";
		const std::string snakeHead		= "SNAKE_HEAD";

		namespace BrickKeyes
		{
			const char wall		= 'B'; //like brick
			const char flor		= 'F';
			const char water	= 'W';
		}
	}

	struct LVLConfigs
	{
		unsigned int width		= 0;
		unsigned int height		= 0;

		std::string pathToWall	= "";
		std::string pathToFlor	= "";
		std::string pathToWater = "";

		unsigned int startPosX	= 0;
		unsigned int startPosY	= 0;

		std::vector<std::string> map;
	};

	//
	using lvlmap = std::vector<std::vector<LVLblock>>;
	//

	class Level
	{
	public:
		class LevelConstructorException : public BaseException
		{
		protected:
			const std::string message;
			const std::string errorString;

		public:
			LevelConstructorException(
				int _line,
				const char* _file,
				const char* _message,
				const char* _errorString);

		public:
			const char* what()				const noexcept override;
			const char* GetType()			const noexcept override;

			const std::string GetErrorString()	const noexcept;
			const std::string GetMessage()		const noexcept;
		};

	private:
		LVLConfigs configs;

	public:
		Level(const LVLConfigs& _configs);

	public:
		Level(const Level&)						= delete;
		Level& operator=(const Level&)			= delete;

	public:
		const LVLConfigs&	GetConfigs()				const;
		const LVLblock&		GetBlock(int _x, int _y)	const;
		const lvlmap&		GetLvlMap()					const;

	private:
		lvlmap lvlMAP;

	private:
		// Return FLOOR if no matches.
		const LVLblock keyToBlock(const char _blockKey) const;

	private:
		const void checkLvlConfigs(const LVLConfigs& cfg) const;

	};

}
#endif

