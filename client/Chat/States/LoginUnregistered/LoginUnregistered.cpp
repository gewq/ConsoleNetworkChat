#include "LoginUnregistered.h"

#include <iostream>
#include <memory>


namespace {
  //Возможный выбор пользователя
  enum {
    INPUT_AGAIN = 1,
    REGISTRATION
  };
}



LoginUnregistered::LoginUnregistered() : State("LoginUnregistered")
{
};



void LoginUnregistered::handle(Chat& chat)
{
  std::cout << "| 1 - Ввести Логин заново | 2 - Регистрация | :  ";
  std::string input;
  std::getline(std::cin >> std::ws, input);

  //Введено более одного символа
  if (input.length() > 1) {
    chat.transitionTo(std::move(std::make_unique<LoginUnregistered>()));
  }
  //Введён один символ
  else {
    //Попытка преобразовать символ в число
    try {
      int choice = std::stoi(input);
      handleChoice(chat, choice);
    }
    //Символ не число - вернуться в начало ко вводу
    catch (const std::invalid_argument&) {
      chat.transitionTo(std::move(std::make_unique<LoginUnregistered>()));
    }
  }
}



void LoginUnregistered::handleChoice(Chat& chat, int choice)
{
  switch (choice) {
    case INPUT_AGAIN: {
      chat.transitionTo(std::move(std::make_unique<LoginInput>()));
      break;
    }
    case REGISTRATION: {
      chat.transitionTo(std::move(std::make_unique<CreateLogin>()));
      break;
    }
    default: {
      std::cin.clear();
      chat.transitionTo(std::move(std::make_unique<LoginUnregistered>()));
      break;
    }
  }
}