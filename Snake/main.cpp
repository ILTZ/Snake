#include <iostream>
#include <exception>



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
	catch (std::exception& _ex)
	{
		std::cout << _ex.what() << std::endl;
	}
}
