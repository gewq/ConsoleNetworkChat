/**
\file SocketCreation_Exception.h
\brief Класс SocketCreation_Exception - класс-обработчик исключения "Ошибка при создании сокета"
*/

#pragma once

#include <string>
#include <exception>

class SocketCreation_Exception : public std::exception {
  public:
    SocketCreation_Exception();

    virtual const char* what() const noexcept override;
};