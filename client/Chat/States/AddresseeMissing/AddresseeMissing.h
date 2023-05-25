/**
\file AddresseeMissing.h
\brief Класс-обработчик состояния "Ник адресата не зарегистрирован"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class AddresseeMissing : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    AddresseeMissing();

    /**
    Обработчик состояния "Ник адресата не зарегистрирован"
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