#include "UserInChat.h"

#include <iostream>
#include <memory>


namespace {
  //Возможный выбор пользователя
  enum {
    SEND_MESSAGE = 1,
    READ_MESSAGE,
    SHOW_USERS,
    EXIT,
    REMOVE_ACCOUT
  };
}



UserInChat::UserInChat() : State("UserInChat")
{
};



void UserInChat::handle(Chat& chat)
{
  const std::string menu = "| " +
  std::to_string(SEND_MESSAGE) + " - Отправить сообщение | " + 
  std::to_string(READ_MESSAGE) + " - Прочитать сообщения | " + 
  std::to_string(SHOW_USERS) + " - Список пользователей | " + 
  std::to_string(EXIT) + " - Выход из чата | " + 
  std::to_string(REMOVE_ACCOUT) + " - Удалить аккаунт : ";

  std::cout << menu;
  std::string input;
  std::getline(std::cin >> std::ws, input);

  //Введено более одного символа
  if (input.length() > 1) {
    chat.transitionTo(std::move(std::make_unique<UserInChat>()));
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
      chat.transitionTo(std::move(std::make_unique<UserInChat>()));
    }
  }
}



void UserInChat::handleChoice(Chat& chat, int choice)
{
  switch (choice) {
    case SEND_MESSAGE: {
      chat.transitionTo(std::move(std::make_unique<AddresseeInput>()));
      break;
    }
    case READ_MESSAGE: {
      chat.printMessagesToUser();
      break;
    }
    case SHOW_USERS: {
      chat.printUserList();
      break;
    }
    case EXIT: {
      chat.transitionTo(std::move(std::make_unique<Start>()));
      chat.getUser()->reset();
      break;
    }
    case REMOVE_ACCOUT: {
      chat.removeAccount();
      chat.transitionTo(std::move(std::make_unique<Start>()));
      break;
    }
    default: {
      std::cin.clear();
      chat.transitionTo(std::move(std::make_unique<UserInChat>()));
      break;
    }
  }
}