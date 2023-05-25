/**
\file LoginRegistered.h
\brief Класс-обработчик состояния "Логин уже зарегистрирован"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class LoginRegistered : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    LoginRegistered();

    /**
    Обработчик состояния "Логин уже зарегистрирован"
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