#include "LoginInput.h"

#include <iostream>
#include <memory>

#include "../../Server/Server.h"


LoginInput::LoginInput() : State("LoginInput")
{
};



void LoginInput::handle(Chat& chat)
{
  std::cout << "Введите Ваш Логин (допустимые символы 'a'-'z', 'A'-'Z', '0'-'9'): ";
  std::string login;
  std::getline(std::cin >> std::ws, login);

  //Допустимые символы
  if (chat.isCorrectValue(login)) {
    //Логин зарегистрирован
    if (server::isLoginRegistered(login)) {
      chat.getUser()->setLogin(login);
      chat.transitionTo(std::move(std::make_unique<PasswordInput>()));
    }
    
    //Логин не зарегистрирован
    else {
      std::cout << "Логин не зарегистрирован!\n";
      chat.transitionTo(std::move(std::make_unique<LoginUnregistered>()));
    }
  }

  //Недопустимые символы
  else {
    std::cout << "Некорректные символы.\n";
    std::cin.clear();
    chat.transitionTo(std::move(std::make_unique<LoginInput>()));
  }
}