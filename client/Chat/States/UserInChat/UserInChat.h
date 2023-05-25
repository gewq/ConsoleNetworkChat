/**
\file UserInChat.h
\brief Класс-обработчик состояния "ПОЛЬЗОВАТЕЛЬ В ЧАТЕ"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class UserInChat : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    UserInChat();

    /**
    Обработчик состояния "ПОЛЬЗОВАТЕЛЬ В ЧАТЕ"
    */
    virtual void handle(Chat& chat) override;

  private:
    /**
    Обработчик ввода пользователя в зависимости от введённого числа
    \param[in] chat Указатель на объект чата для которого выполнять обработку
    \param[in] choice Число которое ввёл пользователь
    */
    void handleChoice(Chat& chat, int choice);
};