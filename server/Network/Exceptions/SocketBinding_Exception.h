/**
\file SocketBinding_Exception.h
\brief Класс SocketBinding_Exception - класс-обработчик исключения "Ошибка при связывании сокета"
*/

#pragma once

#include <string>
#include <exception>

class SocketBinding_Exception : public std::exception {
  public:
    SocketBinding_Exception();

    virtual const char* what() const noexcept override;
};