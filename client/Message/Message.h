/**
\file Message.h
\brief Класс инкапсулирует данные о сообщении

Содержит поля:
- имя пользователя от кого сообщение
- текст сообщения
*/

#pragma once

#include <string>


class Message {
  public:
    /**
    Конструктор по-умолчанию
    */
    Message() = delete;

    /**
    Параметризованный конструктор
    \param[in] nameUserFrom Ник пользователя от которого сообщение
    \param[in] nameUserTo Ник пользователя кому адресовано сообщение
    \param[in] text Текст сообщения
    */
    Message(const std::string& nameUserFrom, const std::string& text);
    /**
    \return Ник пользователя от которого сообщение
    */
    const std::string& getNameFrom() const;

    /**
    \return Ник пользователя кому сообщение
    */
    const std::string& getText() const;

  private:
    const std::string nameUserFrom_;  ///<Имя отправителя сообщения
    const std::string text_;  ///<Текст сообщения
};



namespace message {
  /**
  Запустить тестирование методов класса
  */
  void test();
}