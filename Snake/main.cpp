#include <iostream>
#include <exception>

#include "App.h"

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

}
