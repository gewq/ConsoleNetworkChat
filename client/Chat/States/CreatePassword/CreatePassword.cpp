#include "CreatePassword.h"

#include <iostream>
#include <memory>

// #include "../../DataBase/DataBase.h"
#include "../../Server/Server.h"
#include "../../SHA_1/SHA_1_Wrapper.h"


CreatePassword::CreatePassword() : State("CreatePassword")
{
};



void CreatePassword::handle(Chat& chat)
{
  std::cout << "Придумайте Пароль: ";
  std::string password;
  std::getline(std::cin >> std::ws, password);

  //Допустимые символы
  if (chat.isCorrectValue(password)) {
    server::addUser(chat.getUser()->getName(),
                    chat.getUser()->getLogin(),
                    sha_1::hash(password));

    std::cout << "Вы успешно зарегистрированы!\n"
        << chat.getUser()->getName() << ", добро пожаловать в Чат!\n";
    chat.transitionTo(std::move(std::make_unique<UserInChat>()));
  }

  //Недопустимые символы
  else {
    std::cout << "Некорректные символы.\n";
    std::cin.clear();
    chat.transitionTo(std::move(std::make_unique<CreatePassword>()));
  }
}