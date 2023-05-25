/**
\file AddresseeInput.h
\brief Класс-обработчик состояния "ВВОД АДРЕСАТА"
*/

#pragma once

#include "../../../State/State.h"
#include "../../Chat.h"

class AddresseeInput : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    AddresseeInput();

    /**
    Обработчик состояния "ВВОД АДРЕСАТА"
    */
    virtual void handle(Chat& chat) override;
};