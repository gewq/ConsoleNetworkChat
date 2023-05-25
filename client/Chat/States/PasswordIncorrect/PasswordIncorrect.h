/**
\file PasswordIncorrect.h
\brief Класс-обработчик состояния "ПАРОЛЬ НЕВЕРНЫЙ"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class PasswordIncorrect : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    PasswordIncorrect();

    /**
    Обработчик состояния "ПАРОЛЬ НЕВЕРНЫЙ"
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