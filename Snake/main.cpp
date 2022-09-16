#include <iostream>
#include <exception>

#include "App.h"
#include "BaseDrawable.h"

#include "ConfigLoader.h"

namespace ConstData
{
	const std::string pathToConfig = ".\\ResourcesConfigs\\Configs.json";
}




int main()
{
	try
	{
		App app;
		return app.Run();
	}
	catch (std::exception& _ex)
	{
		std::cout << _ex.what() << std::endl;
	}



	return 0;
}
