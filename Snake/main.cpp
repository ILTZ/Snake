
#include "App.h"
#include <Windows.h>

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
	catch (...)
	{
		MessageBoxA(nullptr, "Unknown exception", "Uncknown exception", MB_OK | MB_ICONERROR);
	}
}
