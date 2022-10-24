#include <iostream>
#include <exception>

#include <Windows.h>
#undef min
#undef max

#include "App.h"

//���� �����:
//1. ��������� - ������
//2. ���� ���� � ������ ������������ ������
//3. ���������� ������ ������������� ���� ���������, ���� ���������������� �������. - ����� ����



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
