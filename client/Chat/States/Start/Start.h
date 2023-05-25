/**
\file Start.h
\brief Класс-обработчик состояния "НИКТО НЕ ЗАЛОГИНЕН"
*/

#pragma once

#include <memory>

#include "../../../State/State.h"
#include "../../Chat.h"


class Start : public State {
  public:
    /**
    Конструктор по-умолчанию
    */
    Start();

    /**
    Обработчик состояния "НИКТО НЕ ЗАЛОГИНЕН"
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