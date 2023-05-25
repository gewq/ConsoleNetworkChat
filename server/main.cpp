#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include "Network/Network.h"
#include "Handler/Handler.h"
#include "DataBase/DataBase.h"

namespace{
  const int PORT = 7777;
}



int main()
{
  try{
    database::test();
    database::initialize();
    network::initialize(PORT);
    while(true){
      network::startListen();
      // while(true){
        std::string message = "";
        network::receive(&message);
        handler::handle(message);
        message.clear();
      // }
    }
    network::disconnect();
  }
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Undefined exception" << std::endl;
	}
  return EXIT_SUCCESS;
}