#include "MaxClients_Exception.h"



MaxClientExceeds_Exception::MaxClientExceeds_Exception() : std::exception()
{
}



const char* MaxClientExceeds_Exception::what() const noexcept
{
	return "Error: Socket is unable to listen new connections";
}