#include "PasswordInput.h"

#include <iostream>
#include <memory>

#include "../../SHA_1/SHA_1_Wrapper.h"
#include "../../Server/Server.h"


PasswordInput::PasswordInput() : State("PasswordInput")
{
};



void PasswordInput::handle(Chat& chat)
{
  std::cout << "Введите Пароль: ";
  std::string password;
  std::getline(std::cin >> std::ws, password);

  //Допустимые символы
  if (chat.isCorrectValue(password)) {
    const std::string login = chat.getUser()->getLogin();
	  std::string passwordHash = sha_1::hash(password);

    //Пароль правильный
    if (server::isPasswordRight(login, passwordHash)) {
      //Загрузить из базы и задать Ник текущего пользователя
      const std::string name = server::getNickname(login);
      chat.getUser()->setName(name);
      std::cout << chat.getUser()->getName() << ", добро пожаловать в Чат!\n";
      chat.transitionTo(std::move(std::make_unique<UserInChat>()));
      chat.printMessagesToUser();
    }

    //Пароль неверный
    else {
      std::cout << "Пароль неверный!\n";
      chat.transitionTo(std::move(std::make_unique<PasswordIncorrect>()));
    }
  }

  //Недопустимые символы
  else {
    std::cout << "Некорректные символы.\n";
    std::cin.clear();
    chat.transitionTo(std::move(std::make_unique<PasswordInput>()));
  }
}