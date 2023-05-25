#include "State.h"

State::State(const std::string& name) : name_(name)
{
}



State::~State()
{
}



const std::string& State::getName() const
{
	return name_;
}