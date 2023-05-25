#include "Handler.h"

#include "../DataBase/DataBase.h"
#include "../Network/Network.h"


namespace{
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


//Проверить Логин на наличие в базе
static void isLoginRegistered(const std::string& request);

//Проверить правильный ли Пароль
static void isPasswordRight(const std::string& request);

//Проверить Ник на наличие в базе
static void isNicknameRegistered(const std::string& request);

//Прислать Ник по Логину
static void sendNickname(const std::string& request);

//Прислать Ники всех пользователей
static void sendAllNicknames();

//Прислать количество зарегистрированных пользователей
static void sendNumberUsers();

//Прислать сообщения пользователю
static void sendMessages(const std::string& request);

//Добавить пользователя в Базу
static void addUser(const std::string& request);

//Добавить сообщение пользователю в Базу
static void addMessage(const std::string& request);

//Удалить аккаунт пользователя по Логину
static void removeUser(const std::string& request);



void handler::handle(const std::string& request)
{
  //Message - Код_Команды|АРГУМЕНТ_1:...
  //Определить код команды - от начала строки до первого '|'
  const std::string codeCommand = request.substr(0, request.find("|"));
  try {
    int command = std::stoi(codeCommand);

    switch (command){
      case IS_LOGIN_REGISTERED: {
        isLoginRegistered(request);
        break;
      }
      case IS_PASSWORD_RIGHT: {
        isPasswordRight(request);
        break;
      }
      case IS_NICKNAME_REGISTERED: {
        isNicknameRegistered(request);
        break;
      }
      case REQUEST_NICKNAME: {
        sendNickname(request);
        break;
      }
      case REQUEST_ALL_NICKNAMES: {
        sendAllNicknames();
        break;
      }
      case REQUEST_NUMBER_USERS: {
        sendNumberUsers();
        break;
      }
      case REQUEST_MESSAGES: {
        sendMessages(request);
        break;
      }
      case ADD_USER: {
        addUser(request);
        break;
      }
      case ADD_MESSAGE: {
        addMessage(request);
        break;
      }
      case REMOVE_USER: {
        removeUser(request);
        break;
      }
      default:
        break;
    }
  }
  catch (const std::invalid_argument&) {
  }
}



//Распарсить строку на слова по разделителю и поместить в result
static void parse (std::shared_ptr<std::vector<std::string> > result,
                  const std::string& input,
                  const std::string& delimiter);


static void isLoginRegistered(const std::string& request)
{
  //request - Код_Команды|LOGIN|
  std::string message = request;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, message, "|");
  const std::string login = result->at(1);

  std::string response = "false";
  //Проверить Логин в базе
  if (database::isLoginRegistered(login)){
    response = "true";
  }
  network::response(response);
}



static void isNicknameRegistered(const std::string& request)
{
  //request - Код_Команды|NICKNAME|
  std::string message = request;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, message, "|");
  const std::string nickname = result->at(1);

  std::string response = "false";
  //Проверить Ник в базе
  if (database::isNicknameRegistered(nickname)){
    response = "true";
  }
  network::response(response);
}



static void isPasswordRight(const std::string& request)
{
  std::string response = "false";

  //request - Код_Команды|LOGIN|HASHPASSWORD|
  std::string message = request;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, message, "|");
  const std::string login = result->at(1);
  const std::string passwordHash = result->at(2);

  //Проверить Пароль в базе
  if (database::isPasswordRight(login, passwordHash)){
    response = "true";
  }
  network::response(response);
}



static void sendNickname(const std::string& request)
{
  //request - Код_Команды|LOGIN|
  std::string message = request;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, message, "|");
  const std::string login = result->at(1);

  //Получить Ник из Базы
  const std::string nickname = database::getNickname(login);
  std::string response = "";
  if (nickname.empty()){
    response = "false";
  }
  else{
    response = nickname;
  }

  network::response(response);
}



static void sendAllNicknames()
{
  //Message - Код_Команды
  auto nicknames = std::make_shared<std::vector<std::string> >();
  database::loadUserNames(nicknames);

  //Собрать Ники в ответное сообщение
  std::string response = "";
  for (const auto& name : *nicknames) {
    response += name + "|";
	}
  network::response(response);
}



static void sendNumberUsers()
{
  //Message - Код_Команды
  //Запросить в Базе
  std::string response = std::to_string(database::getNumberUsers());
  network::response(response);
}



static void sendMessages(const std::string& request)
{
  //request - Код_Команды|LOGIN|
  std::string message = request;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, message, "|");
  const std::string login = result->at(1);

  //Загрузить сообщения
  auto messagesToUser = std::make_shared<std::list<Message> >();
  database::loadMessages(login, messagesToUser);

  //Сформировать ответное сообщение в формате
  //NICK_FROM:MESSAGE:|NICK_FROM:MESSAGE:|...
  std::string response = "";
  if (!messagesToUser->empty()){
    std::cout << "Print messages:\n";
    for (const auto& message : *messagesToUser) {
      response += message.getNameFrom() + ":" + message.getText() + ":|";
    }
  }
  std::cout << response << std::endl;
  network::response(response);
}



static void addUser(const std::string& request)
{
  //Message - Код_Команды|NICKNAME|LOGIN|HASHPASSWORD|
  std::string message = request;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, message, "|");
  const std::string name = result->at(1);
  const std::string login = result->at(2);
  const std::string passwordHash = result->at(3);

  //Добавить в базу
  database::addUser(name, login, passwordHash);

  const std::string response = "true";
  network::response(response);
}



static void addMessage(const std::string& input)
{
  //input - Код_Команды|NICKNAME_TO|NICKNAME_FROM|MESSAGE|
  std::string request = input;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, request, "|");
  const std::string nicknameTo = result->at(1);
  const std::string nicknameFrom = result->at(2);
  const std::string message = result->at(3);

  //Добавить сообщение в Базу
  database::pushMessage(nicknameTo,
                        Message(nicknameFrom, message));

  const std::string response = "true";
  network::response(response);
}



static void removeUser(const std::string& request)
{
  //request - Код_Команды|LOGIN|
  std::string message = request;

  //Распарсить входное сообщение
  auto result = std::make_shared<std::vector<std::string> >();
  parse(result, message, "|");
  const std::string login = result->at(1);

  //Удалить аккаунт пользователя
  database::removeUser(login);

  const std::string response = "true";
  network::response(response);
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