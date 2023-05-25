#include "PasswordIncorrect.h"

#include <iostream>
#include <memory>


namespace {
  //Возможный выбор пользователя
  enum {
    INPUT_AGAIN = 1,
    TO_MAIN_MENU
  };
}



PasswordIncorrect::PasswordIncorrect() : State("PasswordIncorrect")
{
};



void PasswordIncorrect::handle(Chat& chat)
{
  std::cout << "| 1 - Ввести пароль заново | 2 - Отменить вход | :  ";
  std::string input;
  std::getline(std::cin >> std::ws, input);

  //Введено более одного символа
  if (input.length() > 1) {
    chat.transitionTo(std::move(std::make_unique<PasswordIncorrect>()));
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
      chat.transitionTo(std::move(std::make_unique<PasswordIncorrect>()));
    }
  }
}



void PasswordIncorrect::handleChoice(Chat& chat, int choice)
{
  switch (choice) {
    case INPUT_AGAIN: {
      chat.transitionTo(std::move(std::make_unique<PasswordInput>()));
      break;
    }
    case TO_MAIN_MENU: {
      chat.transitionTo(std::move(std::make_unique<Start>()));
      break;
    }
    default: {
      std::cin.clear();
      chat.transitionTo(std::move(std::make_unique<PasswordIncorrect>()));
      break;
    }
  }
}