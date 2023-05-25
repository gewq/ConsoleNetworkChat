#include "SocketCreation_Exception.h"



SocketCreation_Exception::SocketCreation_Exception() : std::exception()
{
}



const char* SocketCreation_Exception::what() const noexcept
{
	return "Error: Socket creation failure";
}