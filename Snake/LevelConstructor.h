#ifndef LVLCONSTR_H
#define LVLCONSTR_H

#include <string>
#include <vector>

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

	enum class AutoConstr
	{
		// xxxxxxxxxxxx
		// x	      x
		// x		  x
		// x          x
		// xxxxxxxxxxxx
		EDGES	= 0,

		// xx        xx
		// x          x
		//
		// x          x
		// xx        xx
		CORNER	= 1,

		// x          x
		//   x      x
		//    x    x
		//   x      x
		// x          x
		DISCRET = 2,

		NONE	= 3
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
		const std::string mode		= "mode";
		const std::string handM		= "hand";
		const std::string autoM		= "auto";

		const std::string width		= "width";
		const std::string height	= "height";
		const std::string startPos	= "startPos";

		const std::string flor		= "florPath";
		const std::string water		= "waterPath";
		const std::string wall		= "wallPath";

		const std::string waterPos	= "waterPos";
		const std::string wallPos	= "wallPos";

		const std::string map		= "map";

		// if we have autoMode
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

		AutoConstr wallPos		= AutoConstr::NONE;
		AutoConstr waterPos		= AutoConstr::NONE;

		bool autoContr			= true;

		std::vector<std::string> map;
	};

	//
	using lvlmap = std::vector<std::vector<LVLblock>>;
	//

	class Level
	{
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

		void fillFlor(lvlmap& _vec);
		void fillWall(lvlmap& _vec,		AutoConstr _wallPos = AutoConstr::NONE);
		void fillWater(lvlmap& _vec,	AutoConstr _waterPos = AutoConstr::NONE);

	private:
		// Return FLOOR if no matches.
		const LVLblock keyToBlock(const char _blockKey) const;
	};

}
#endif

