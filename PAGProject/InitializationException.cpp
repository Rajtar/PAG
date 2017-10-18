#include <exception>
#include <stdexcept>

class InitializationException : public std::exception
{
public:

	virtual const char* what() const throw()
	{
		return "Error during initialization";
	}
};