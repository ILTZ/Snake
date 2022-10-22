#include <iostream>
#include <exception>



#include "App.h"


//Цели блять:
//1. Лидерборд - готово
//2. Фикс бага с резким перемещением змейки
//3. Добалвение режима использование либо дефолтных, либо пользовательских ассетов. - нахуй надо



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
