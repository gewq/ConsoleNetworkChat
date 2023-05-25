/**
\file PasswordInput.h
\brief Класс-обработчик состояния "Ввод Пароля для входя"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class PasswordInput : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    PasswordInput();

    /**
    Обработчик состояния "ЛОГИН КОРРЕКТНЫЙ"
    */
    virtual void handle(Chat& chat) override;
};