/**
\file Network.h
\brief Модуль "Сеть" - содержит методы работы с приёмом/передачей данных по сети
*/

#pragma once

#include <iostream>


namespace network{
  /**
  Создать сервер - сетевое соединение
  \param[in] port Порт сервера
  */
  void initialize(uint16_t port);

  /**
  Начать прослушивать порт и принимать входящие запросы
  */
  void startListen();

  /**
  Получить сообщение
  \param[in] message Полученное сообщение 
  */
  void receive(std::string* message);

  /**
  Ответить клиенту
  \param[in] message Сообщение - ответ
  */
  void response(const std::string& message);

  /**
  Завершить сетевое соединение
  */  
  void disconnect();
}