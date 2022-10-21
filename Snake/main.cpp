#include <iostream>
#include <exception>

#include "App.h"

namespace ConstData
{
	const std::string pathToConfig = ".\\ResourcesConfigs\\Configs.json";
}

//Цели блять:
//1. Лидерборд
//2. Фикс бага с резким перемещением змейки
//3. Добалвение режима использование либо дефолтных, либо пользовательских ассетов.



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
