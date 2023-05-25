/**
\file SocketConnection_Exception.h
\brief Класс SocketConnection_Exception - класс-обработчик исключения "Соединение не установлено"
*/

#pragma once

#include <string>
#include <exception>

class SocketConnection_Exception : public std::exception {
  public:
    SocketConnection_Exception();

    virtual const char* what() const noexcept override;
};