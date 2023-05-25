#pragma once

#include <string>
#include <vector>
#include <list>
#include <memory>

#include "../Message/Message.h"


namespace server{
  /**
  Подключиться к серверу
  */
  void connect();

  /**
  Запросить у сервера зарегистрирован ли Логин
  \param[in] login Логин
  \return Признак зарегистрирован ли Логин
  */  
  bool isLoginRegistered(const std::string& login);

  /**
  Запросить у сервера зарегистрирован ли Ник
  \param[in] nickname Ник
  \return Признак зарегистрирован ли Ник
  */  
  bool isNicknameRegistered(const std::string& nickname);

  /**
  Запросить у сервера правильный ли пароль
  \param[in] login Логин
  \param[in] passwordHash Хэш Пароля
  \return Признак правильный ли пароль
  */  
  bool isPasswordRight(const std::string& login,
                      const std::string& passwordHash);
  
  /**
  Запросить у сервера Ник по Логину
  \param[in] login Логин
  \return Ник
  */  
  std::string getNickname(const std::string& login);

  /**
  Запросить у сервера Ники всех пользователей
  \param[in] nicknames Результат - указатель на вектор Ников
  */
  void getAllNicknames(std::shared_ptr<std::vector<std::string> > nicknames);

  /**
  Запросить у сервера количество зарегистрированных пользователей
  \return Количество зарегистрированных пользователей
  */
  int getNumberUsers();

  /**
  Запросить у сервера сообщения пользователю
  \param[in] login Логин пользователя
  */  
  void getMessages(const std::string& login,
                  std::shared_ptr<std::list<Message> >& messages);

  /**
	Запросить сервер добавить нового пользователя в Базу
	\param[in] name Ник пользователя
	\param[in] login Логин пользователя
	\param[in] passwordHash Хэш пароля
	*/
	void addUser(const std::string& name,
              const std::string& login,
              const std::string& passwordHash);

  /**
	Запросить сервер добавить сообщение пользователю в Базу
	\param[in] nameTo Ник пользователя которому сообщение
	\param[in] nameFrom Ник пользователя от которого сообщение
	\param[in] message Сообщение
	*/
	void addMessage(const std::string& nameTo,
                  const std::string& nameFrom,
                  const std::string& message);

  /**
  Запросить у сервера удалить аккаунт пользователя по Логину
  \param[in] login Логин
  */  
  void removeUser(const std::string& login);

}