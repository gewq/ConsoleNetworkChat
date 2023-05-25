/**
\file DataBase.h
\brief Модуль "База данных" - содержит данные о Пользователях
Предоставляет функции работы с базой данных Пользователей:
- проверить есть ли заданный Логин в Базе
- проверить корректный ли Пароль
- добавить пользователя в Базу
*/

#pragma once
#include <string>
#include <vector>
#include <list>
#include <memory>

#include "../Message/Message.h"


namespace database {
	/**
	Заполнить базу начальными значениями
	*/
	void initialize();

	/**
	Добавить нового пользователя в базу
	\param[in] name Ник пользователя
	\param[in] login Логин пользователя
	\param[in] passwordHash Хэш пароля
	*/
	void addUser(const std::string& name,
							const std::string& login,
							const std::string& passwordHash);

	/**
	Проверить есть ли в базе заданный Логин
	\param[in] login Логин
	\return Признак наличия заданного Логина в базе
	*/
	bool isLoginRegistered(const std::string& login);

	/**
	Проверить есть ли в базе заданный Ник
	\param[in] name Ник
	\return Признак наличия заданного Ника в базе
	*/
	bool isNicknameRegistered(const std::string& name);

	/**
	Проверить соответствует ли Пароль заданному Логину
	\param[in] login Логин
	\param[in] passwordHash Хэш пароля
	\return Признак правильный ли Пароль
	*/
	bool isPasswordRight(const std::string& login,
											const std::string& passwordHash);

	/**
	Поместить в базу сообщение от одного пользователя другому
	\param[in] nameAdressee Ник пользователя кому сообщение
	\param[in] message Сообщение
	*/
	void pushMessage(const std::string& nameAdressee,
									const Message& message);

	/**
	Загрузить сообщения, адресованные заданному пользователю
	\param[in] login Логин пользователя
	\param[in] destination Указатель на список в который поместить сообщения
	*/
	void loadMessages(const std::string& login,
		std::shared_ptr<std::list<Message> >& messages);

	/**
	Удалить заданного пользователя из базы
	\param[in] login Логин пользователя которого удалить
	*/
	void removeUser(const std::string& login);

	/**
	Вернуть ник по логину
	Если пользователь не зарегистрирован - возвращает пустую строку
	\param[in] login Логин
	\return Ник пользователя
	*/
	std::string getNickname(const std::string& login);

	/**
	\return Количество зарегистрированных пользователей
	*/
	size_t getNumberUsers();

	/**
	Загрузить имена зарегистрированных пользователей
	\param[in] userNames Умный указатель на вектор в который поместить имена пользователей
	*/
	void loadUserNames(std::shared_ptr<std::vector<std::string> > userNames);

	/**
	Запустить тесты методов модуля
	*/
	void test();
}