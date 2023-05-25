#include "SocketConnection_Exception.h"



SocketConnection_Exception::SocketConnection_Exception() : std::exception()
{
}



const char* SocketConnection_Exception::what() const noexcept
{
	return "Error: Socket connection failure";
}