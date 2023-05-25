#include "AddresseeInput.h"

#include <iostream>
#include <memory>

#include "../../Server/Server.h"


AddresseeInput::AddresseeInput() : State("AddresseeInput")
{
};



void AddresseeInput::handle(Chat& chat)
{
  std::cout << "Введите Ник адресата (all - отправить всем): ";
  std::string nameAdressee;
  std::getline(std::cin >> std::ws, nameAdressee);

  //Зарегистрирован только один пользователь
  if (server::getNumberUsers() == 1) {
    std::cout << "Вы единственный пользователь чата\n";
    chat.transitionTo(std::move(std::make_unique<UserInChat>()));
  }

  //Неверное имя адресата
  else if ( (nameAdressee != "all") &&
            (!server::isNicknameRegistered(nameAdressee)) ) {
    std::cout << "Пользователь с таким Ником не зарегистрирован.\n";
    chat.transitionTo(std::move(std::make_unique<AddresseeMissing>()));
  }

  //Адресат корректный
  else {
    std::cout << "Введите сообщение: ";
    std::string textMessage;
    std::getline(std::cin >> std::ws, textMessage);

    //Текст введён
    if (!textMessage.empty()) {
      server::addMessage(nameAdressee,
                        chat.getUser()->getName(),
                        textMessage);
      std::cout << "Сообщение отправлено\n";
    }

    //Текст не введён
    else {
      std::cout << "Сообщение не отправлено (отсутствует текст сообщения)\n";
    }
    chat.transitionTo(std::move(std::make_unique<UserInChat>()));
  }
}