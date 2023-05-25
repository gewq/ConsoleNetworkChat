/**
\file User.h
\brief Класс содержит данные о пользователе
Класс инкапсулирует в себе параметры пользователя:
- Ник (имя) - по нику он будет известен другим пользователям
- Логин - имя по которому он будет заходить в чат
- Хэш Пароля
*/

#pragma once

#include <string>
#include <list>
#include <memory>

#include "../Message/Message.h"


class User {
	public:
		User();
		User(const std::string& name,
			const std::string& login,
			const std::string& hashPassword);

		/**
		Перегрузка оператора '==' для поиска пользователя в базе данных
		с использованием алгоритмов STL
		*/
		bool operator==(User other) const;

		/**
		\return Ник пользователя
		*/
		std::string getName() const;

		/**
		\return Логин пользователя
		*/
		std::string getLogin() const;

		/**
		\return Хеш Пароля
		*/
		std::string getHashPassword() const;

		/**
		\return Указатель на список сообщений пользователю
		*/
		std::shared_ptr<std::list<Message> > getMessageList() const;

		/**
		Задать пользователю Имя
		\param[in] name Имя
		*/
		void setName(const std::string& name);

		/**
		Задать пользователю Логин
		\param[in] login Логин
		*/
		void setLogin(const std::string& login);

		/**
		Задать пользователю Сообщение
		\param[in] message Сообщение
		*/
		void setMessage(const Message& message);

		/**
		Присвоить значения полей класса - пустая строка
		*/
		void reset();

	private:
		std::string name_;		///<Ник
		std::string login_;		///<Логин
		std::string hashPassword_;	///<Хеш Пароля
		std::shared_ptr<std::list<Message> > messages_;	///<Сообщения пользователю
};



namespace user {
	/**
	Запустить тестирование методов класса
	*/
	void test();
}