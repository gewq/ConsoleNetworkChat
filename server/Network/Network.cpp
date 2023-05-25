#include "Network.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Exceptions/SocketCreation_Exception.h"
#include "Exceptions/SocketBinding_Exception.h"
#include "Exceptions/MaxClients_Exception.h"
#include "Exceptions/SocketConnection_Exception.h"


namespace{
  const uint16_t MAX_LENGTH_MESSAGE = 1024;  //MAX размер пересылаемых сообщений
  const uint16_t MAX_CLIENTS = 5;

  int socketDescriptor;
  int connection;

  socklen_t length;
  struct sockaddr_in serverAddress;
  struct sockaddr_in client;

  char inputBuffer[MAX_LENGTH_MESSAGE];
}


static int createSocket();
static void bindSocket(int socket_descriptor, uint16_t port);



void network::initialize(uint16_t port)
{
  socketDescriptor = createSocket();
  bindSocket(socketDescriptor, port);
}



void network::startListen()
{
  //Сервер на приём данных
  std::cout << "Server is listening to new connections..." << std::endl;
  int connection_status = listen(socketDescriptor, MAX_CLIENTS);
  if (connection_status == -1){
    throw MaxClientExceeds_Exception();
  }

  length = sizeof(client);
  connection = accept(socketDescriptor, (struct sockaddr*)&client, &length);
  if (connection == -1){
    throw SocketConnection_Exception();
  }
}



void network::receive(std::string* message)
{
  message->clear();
  read(connection, inputBuffer, MAX_LENGTH_MESSAGE);
  *message = inputBuffer;
  std::cout << "Received:" << *message << std::endl;
}



void network::response(const std::string& message)
{
  ssize_t bytes = write(connection, message.c_str(), MAX_LENGTH_MESSAGE);
  //Если передали >= 0 байт, значит пересылка прошла успешно
  if(bytes >= 0){
    // std::cout << "Data send to the server successfully!\n";
  }
}



void network::disconnect()
{
  close(socketDescriptor);
}



static int createSocket()
{
  int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_descriptor == -1){
		throw SocketCreation_Exception();
  }
  return socket_descriptor;
}



static void bindSocket(int socket_descriptor, uint16_t port)
{
  //Задать сетевые параметры сервера
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  //Приём на все сетевые интерфейсы
  serverAddress.sin_port = htons(port); //Порт
  serverAddress.sin_family = AF_INET;   //IPv4
  //Привязать сокет
  int bind_status = bind(socket_descriptor,
                            (struct sockaddr*) &serverAddress,
                            sizeof(serverAddress));
  if (bind_status == -1){
    throw SocketBinding_Exception();
  }
}