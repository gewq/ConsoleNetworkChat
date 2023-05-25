/**
\file CreatePassword.h
\brief Класс-обработчик состояния "Создать Пароль нового пользователя"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"


class CreatePassword : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    CreatePassword();

    /**
    Обработчик состояния "Создать Пароль нового пользователя"
    */
    virtual void handle(Chat& chat) override;
};