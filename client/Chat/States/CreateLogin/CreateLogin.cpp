#include "CreateLogin.h"

#include <iostream>
#include <memory>

#include "../../Server/Server.h"



CreateLogin::CreateLogin() : State("CreateLogin")
{
};



void CreateLogin::handle(Chat& chat)
{
  std::cout << "Придумайте Логин (допустимые символы 'a'-'z', 'A'-'Z', '0'-'9'): ";
  std::string login;
  std::getline(std::cin >> std::ws, login); //Функция ввода ws использует пробелы из входного потока

  //Допустимые символы
  if (chat.isCorrectValue(login)) {
    chat.getUser()->setLogin(login);
    //Такой Логин уже зарегистрирован
    if (server::isLoginRegistered(login)) {
      std::cout << "Логин уже зарегистрирован!\n";
      chat.transitionTo(std::move(std::make_unique<LoginRegistered>()));
    }

    //Логин уникальный
    else {
      chat.transitionTo(std::move(std::make_unique<CreateNickname>()));
    }
  }

  //Недопустимые символы
  else {
    std::cout << "Некорректные символы.\n";
    std::cin.clear();
    chat.transitionTo(std::move(std::make_unique<CreateLogin>()));
  }
}