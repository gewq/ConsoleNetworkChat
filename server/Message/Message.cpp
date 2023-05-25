#include "Message.h"

#include <assert.h>


Message::Message(const std::string& nameUserFrom,
	const std::string& text) :
	nameUserFrom_(nameUserFrom),
	text_(text)
{
}



const std::string& Message::getNameFrom() const
{
	return nameUserFrom_;
}



const std::string& Message::getText() const
{
	return text_;
}



//========================================================================================================
void message::test()
{
	//Тест параметризованного конструктора и get-методов
	std::string nameUserFrom = "nameUserFrom";
	std::string text = "text";

	Message message(nameUserFrom, text);
	assert(message.getNameFrom() == nameUserFrom);
	assert(message.getText() == text);
}