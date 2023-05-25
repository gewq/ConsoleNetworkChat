#include "SocketBinding_Exception.h"



SocketBinding_Exception::SocketBinding_Exception() : std::exception()
{
}



const char* SocketBinding_Exception::what() const noexcept
{
	return "Error: Socket binding failure";
}