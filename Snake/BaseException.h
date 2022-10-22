#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <string>

class BaseException : std::exception
{
public:

	BaseException(int _line, const char* _file) noexcept;
	const char* what() const noexcept override;

	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

private:

	int line;
	std::string file;

protected:

	mutable std::string whatBuffer;

};



#endif
