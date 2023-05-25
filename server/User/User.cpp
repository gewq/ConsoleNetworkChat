#include "User.h"

#include <assert.h>


User::User() : name_(""), login_(""), hashPassword_(""),
	messages_(std::make_shared<std::list<Message> >())
{
}

User::User(const std::string& name,
	const std::string& login,
	const std::string& hashPassword):
	name_(name), login_(login), hashPassword_(hashPassword),
	messages_(std::make_shared<std::list<Message> >())
{
}



bool User::operator==(User other) const
{
	//Объекты равны если совпадает Логин
	if (login_ == other.login_) {
		return true;
	}
	return false;
}



std::string User::getName() const
{
	return name_;
}



std::string User::getLogin() const
{
	return login_;
}



std::shared_ptr<std::list<Message> > User::getMessageList() const
{
	return messages_;
}



std::string User::getHashPassword() const
{
	return hashPassword_;
}



void User::setName(const std::string& name)
{
	name_ = name;
}



void User::setLogin(const std::string& login)
{
	login_ = login;
}



void User::setMessage(const Message& message)
{
	messages_->push_front(message);
}



void User::reset()
{
	name_.clear();
	login_.clear();
	hashPassword_.clear();
	messages_->clear();
}


//========================================================================================================
static void testConstructorDefault();
static void testConstructorParameterized();
static void testSet();
static void testOperatorEquality();
static void testReset();
static void testMessages();


void user::test()
{
	testConstructorDefault();
	testConstructorParameterized();
	testSet();
	testOperatorEquality();
	testReset();
	testMessages();
}



static void testConstructorDefault()
{
	User user;
	assert(user.getName() == "");
	assert(user.getLogin() == "");
	assert(user.getHashPassword() == "");
}



static void testConstructorParameterized()
{
	const std::string name = "name";
	const std::string login = "login";
	const std::string hashPassword = "5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8";

	User user(name, login, hashPassword);
	assert(user.getName() == name);
	assert(user.getLogin() == login);
	assert(user.getHashPassword() == hashPassword);
}



static void testSet()
{
	User user;
	const std::string name = "name";
	const std::string login = "login";
	user.setName(name);
	user.setLogin(login);
	assert(user.getName() == name);
	assert(user.getLogin() == login);
}



static void testOperatorEquality()
{
	User user1;
	User user2("name", "login", "5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8");
	User user3("name", "login", "d63d5c2879619d7ffd81d029490b4e69b81ff55d");
	User user4("new_name", "new_login", "d63d5c2879619d7ffd81d029490b4e69b81ff55d");

	assert((user1 == user2) == false);
	assert((user2 == user3) == true);
	assert((user2 == user4) == false);
}



static void testReset()
{
	const std::string name = "name";
	const std::string login = "login";
	const std::string hashPassword = "5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8";

	User user(name, login, hashPassword);

	user.reset();
	assert(user.getName() == "");
	assert(user.getLogin() == "");
	assert(user.getHashPassword() == "");
	assert(user.getMessageList()->empty() == true);
}



static void testMessages()
{
	User user("name", "login", "1");

	const std::string nameUserFrom = "nameUserFrom";
	const std::string messageText = "Message to User";

	user.setMessage(Message(nameUserFrom, messageText));

	assert(user.getMessageList()->front().getText() == messageText);
}