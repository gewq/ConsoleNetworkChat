/**
\file LoginIncorrect.h
\brief Класс-обработчик состояния "ЛОГИН НЕКОРРЕКТНЫЙ"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class LoginUnregistered : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    LoginUnregistered();

    /**
    Обработчик состояния "ЛОГИН НЕКОРРЕКТНЫЙ"
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