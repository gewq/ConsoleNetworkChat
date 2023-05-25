#include "Start.h"
#include <iostream>


namespace {
  //Возможный выбор пользователя
  enum {
    SIGN_IN = 1,
    REGISTRATION,
    EXIT
  };
}



Start::Start() : State("Start")
{
};



void Start::handle(Chat& chat)
{
  const std::string menu = "| " +
  std::to_string(SIGN_IN) + " - Вход в чат | " + 
  std::to_string(REGISTRATION) + " - Регистрация | " + 
  std::to_string(EXIT) + " - Выход из программы : ";

  std::cout << menu;
  std::string input;
  std::getline(std::cin >> std::ws, input);

  //Введено более одного символа
  if (input.length() > 1) {
    chat.transitionTo(std::move(std::make_unique<Start>()));
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
      chat.transitionTo(std::move(std::make_unique<Start>()));
    }
  }
}



void Start::handleChoice(Chat& chat, int choice)
{
  switch (choice) {
    case SIGN_IN: {
      chat.transitionTo(std::move(std::make_unique<LoginInput>()));
      break;
    }
    case REGISTRATION: {
      chat.transitionTo(std::move(std::make_unique<CreateLogin>()));
      break;
    }
    case EXIT: {
      chat.exit();
      break;
    }
    default: {
      std::cin.clear();
      chat.transitionTo(std::move(std::make_unique<Start>()));
      break;
    }
  }
}