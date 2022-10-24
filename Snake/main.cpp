#include <iostream>
#include <exception>

#include <Windows.h>
#undef min
#undef max

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
	catch (BaseException& _ex)
	{
		MessageBoxA(nullptr, _ex.what(), _ex.GetType(), MB_OK | MB_ICONERROR);
	}
	catch (std::exception& _ex)
	{
		MessageBoxA(nullptr, _ex.what(), "Other exception", MB_OK | MB_ICONERROR);
	}
}
