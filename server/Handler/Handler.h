/**
\file Handler.h
\brief Модуль "Обработчик" - содержит методы обработки запросов серверу
*/

#include <string>


namespace handler{
  /**
  Обработать входящее сообщение и отправить ответ
  \param[in] request Входящее сообщение
  */
  void handle(const std::string& request);
}