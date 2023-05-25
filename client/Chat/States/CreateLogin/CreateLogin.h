/**
\file CreateLogin.h
\brief Класс-обработчик состояния "Создать Логин нового пользователя"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class CreateLogin : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    CreateLogin();

    /**
    Обработчик состояния "Создать Логин нового пользователя"
    */
    virtual void handle(Chat& chat) override;
};