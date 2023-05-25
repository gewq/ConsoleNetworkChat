#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Server/Server.h"
#include "User/User.h"
#include "Chat/Chat.h"


namespace{
  const int PORT = 7777;
}


/**
Запустить тесты модулей программы
*/
static void test();


int main()
{
  try{
    test();
    std::shared_ptr<bool> isRun = std::make_shared<bool>(true);
		Chat::getInstance()->attach(isRun);

		while (*isRun) {
			Chat::getInstance()->process();
		}
  }
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Undefined exception" << std::endl;
	}
  return EXIT_SUCCESS;
}



static void test()
{
	user::test();
	message::test();
}