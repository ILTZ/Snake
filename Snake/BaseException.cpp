#include "BaseException.h"


BaseException::BaseException(int _line, const char* _file) noexcept
	: line(_line), file(_file)
{

}

const char* BaseException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl << GetOriginString();
	whatBuffer = os.str();

	return whatBuffer.c_str();
}

const char* BaseException::GetType() const noexcept
{
	return "MyException";
}

int BaseException::GetLine() const noexcept
{
	return line;
}

const std::string& BaseException::GetFile() const noexcept
{
	return file;
}

std::string BaseException::GetOriginString() const noexcept
{
	std::ostringstream os;
	os << "[File]" << file << std::endl << "[Line]" << line;

	return os.str();
}