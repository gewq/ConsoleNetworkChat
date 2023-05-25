#include "Server.h"

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Exceptions/SocketCreation_Exception.h"
#include "Exceptions/SocketConnection_Exception.h"



namespace{
  const std::string ADDRESS = "127.0.0.1";
  const int PORT = 7777;

  const int MAX_LENGTH_MESSAGE = 1024;  //MAX размер пересылаемых сообщений
  int socketDescriptor;
  struct sockaddr_in serverAddress;
  char inputBuffer[MAX_LENGTH_MESSAGE];

  //Коды запросов серверу
  enum Command{
    NOTHING,
    IS_LOGIN_REGISTERED,
    IS_PASSWORD_RIGHT,
    IS_NICKNAME_REGISTERED,
    REQUEST_NICKNAME,
    REQUEST_ALL_NICKNAMES,
    REQUEST_NUMBER_USERS,
    REQUEST_MESSAGES,
    ADD_USER,
    ADD_MESSAGE,
    REMOVE_USER
  };
}



void server::connect()
{
  //Создать сокет
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if(socketDescriptor == -1){
    throw SocketCreation_Exception();
  }

  //Задать параметры сервера
  serverAddress.sin_addr.s_addr = inet_addr(ADDRESS.c_str());
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_family = AF_INET;

  //Установить соединение с сервером
  int connection = connect(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  if(connection == -1){
    throw SocketConnection_Exception();
  }
}


/**
Отправить серверу сообщение
\param[in] message Сообщение
*/
static void send(const std::string& message);

//Распарсить строку на слова по разделителю и поместить в result
static void parse (std::shared_ptr<std::vector<std::string> > result,
                  const std::string& input,
                  const std::string& delimiter);



bool server::isLoginRegistered(const std::string& login)
{
  //request - Код_Команды|LOGIN|
  //Сформировать и отправить запрос
  Command command = IS_LOGIN_REGISTERED;
  std::string message = std::to_string(command) + "|" + login + "|";
  connect();
  send(message);

  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  message = inputBuffer;
  if (message == "true"){
    return true;
  }
  return false;
}



bool server::isNicknameRegistered(const std::string& nickname)
{
  //request - Код_Команды|NICKNAME|
  //Сформировать и отправить запрос
  Command command = IS_NICKNAME_REGISTERED;
  std::string message = std::to_string(command) + "|" + nickname + "|";
  connect();
  send(message);

  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  message = inputBuffer;
  if (message == "true"){
    return true;
  }
  return false;
}



bool server::isPasswordRight(const std::string& login,
                            const std::string& passwordHash)
{
  //request - Код_Команды|LOGIN|HASHPASSWORD|
  //Сформировать и отправить запрос
  Command command = IS_PASSWORD_RIGHT;
  std::string message = std::to_string(command) + "|" + login + "|" + passwordHash + "|";
  connect();
  send(message);

  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  message = inputBuffer;
  if (message == "true"){
    return true;
  }

  return false;
}



std::string server::getNickname(const std::string& login)
{
  //request - Код_Команды|LOGIN|
  //Сформировать и отправить запрос
  Command command = REQUEST_NICKNAME;
  std::string message = std::to_string(command) + "|" + login + "|";
  connect();
  send(message);

  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  message = inputBuffer;
  if (message == "false"){
    return "";
  }

  return message;
}



void server::getAllNicknames(std::shared_ptr<std::vector<std::string> > nicknames)
{
  //request - Код_Команды
  //Сформировать и отправить запрос
  Command command = REQUEST_ALL_NICKNAMES;
  std::string message = std::to_string(command);
  connect();
  send(message);

  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  message = inputBuffer;
  nicknames->clear();

  //Распарсить входную строку и поместить ники в вектор
  parse(nicknames, message, "|");
}



int server::getNumberUsers()
{
  //request - Код_Команды
  //Сформировать и отправить запрос
  Command command = REQUEST_NUMBER_USERS;
  std::string message = std::to_string(command);
  connect();
  send(message);

  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  message = inputBuffer;
  int result = std::stoi(message);

  return result;
}



void server::getMessages(const std::string& login,
                        std::shared_ptr<std::list<Message> >& messages)
{
  //request - Код_Команды|LOGIN|
  //Сформировать и отправить запрос
  Command command = REQUEST_MESSAGES;
  std::string message = std::to_string(command) + "|" + login + "|";
  connect();
  send(message);
  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
  const std::string answer = inputBuffer;

  auto _messages = std::make_shared<std::vector<std::string> >();
  parse(_messages, answer, "|");

  //Распарсить каждое отдельное сообщение на Ник отправителя/Текст сообщения
  auto pair = std::make_shared<std::vector<std::string> >();

  for (const auto& message : *_messages) {
    parse(pair, message, ":");
    const std::string nameFrom = pair->at(0);
    const std::string text = pair->at(1);
    messages->push_front(Message(nameFrom, text));
	}
}



void server::addUser(const std::string& name,
                    const std::string& login,
                    const std::string& passwordHash)
{
  //request - Код_Команды|NICKNAME|LOGIN|HASHPASSWORD|
  Command command = ADD_USER;
  std::string message = std::to_string(command) + "|" +
                        name + "|" + login + "|" + passwordHash + "|";
  connect();
  send(message);
  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
}



void server::addMessage(const std::string& nameTo,
                        const std::string& nameFrom,
                        const std::string& message)
{
  //request - Код_Команды|NICKNAME_TO|NICKNAME_FROM|MESSAGE|
  Command command = ADD_MESSAGE;
  std::string messageToServer = std::to_string(command) + "|" +
                                nameTo + "|" + nameFrom + "|" + message + "|";
  connect();
  send(messageToServer);
  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
}



void server::removeUser(const std::string& login)
{
  //request - Код_Команды|LOGIN|
  //Сформировать и отправить запрос
  Command command = REMOVE_USER;
  std::string message = std::to_string(command) + "|" + login + "|";
  connect();
  send(message);

  //Ждать ответ от сервера
  read(socketDescriptor, inputBuffer, MAX_LENGTH_MESSAGE);
}



static void parse (std::shared_ptr<std::vector<std::string> > result,
                  const std::string& input,
                  const std::string& delimiter)
{
  result->clear();
  std::string string = input;
  while (!string.empty()){
    std::string value = string.substr(0, string.find(delimiter));
    string = string.substr(string.find(delimiter)+1);
    result->push_back(value);
  }
}



static void send(const std::string& message)
{
  ssize_t bytes = write(socketDescriptor, message.c_str(), MAX_LENGTH_MESSAGE);
  //Если передали >= 0 байт, значит пересылка прошла успешно
  if(bytes >= 0){
    // std::cout << "Data send to the server successfully!\n";
  }
}