#include "CreateNickname.h"

#include <iostream>
#include <memory>

#include "../../Server/Server.h"



CreateNickname::CreateNickname() : State("CreateNickname")
{
};



void CreateNickname::handle(Chat& chat)
{
  std::cout << "Придумайте Ник: ";
  std::string name;
  std::getline(std::cin >> std::ws, name);

  //Допустимые символы
  if (chat.isCorrectValue(name)) {
    //Такой Ник уже зарегистрирован
    if (server::isNicknameRegistered(name)) {
      std::cout << "Пользователь с таким Ником уже зарегистрирован\n";
      chat.transitionTo(std::move(std::make_unique<CreateNickname>()));
    }
    else{
      chat.getUser()->setName(name);
      chat.transitionTo(std::move(std::make_unique<CreatePassword>()));
    }
  }

  //Недопустимые символы
  else {
    std::cout << "Некорректные символы.\n";
    std::cin.clear();
    chat.transitionTo(std::move(std::make_unique<CreateNickname>()));
  }
}