/**
\file CreateNickname.h
\brief Класс-обработчик состояния "Создать Ник нового пользователя"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class CreateNickname : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    CreateNickname();

    /**
    Обработчик состояния "Создать Ник нового пользователя"
    */
    virtual void handle(Chat& chat) override;
};