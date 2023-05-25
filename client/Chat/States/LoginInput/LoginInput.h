/**
\file LoginInput.h
\brief Класс-обработчик состояния "Ввод Логина для входа"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class LoginInput : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    LoginInput();

    /**
    Обработчик состояния "Ввод Логина для входа"
    */
    virtual void handle(Chat& chat) override;
};