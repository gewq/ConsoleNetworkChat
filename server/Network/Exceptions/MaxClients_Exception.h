/**
\file MaxClients_Exception.h
\brief Класс MaxClientExceeds_Exception - класс-обработчик исключения "Слишком много клиентов подлкючено"
*/

#pragma once

#include <string>
#include <exception>

class MaxClientExceeds_Exception : public std::exception {
  public:
    MaxClientExceeds_Exception();

    virtual const char* what() const noexcept override;
};