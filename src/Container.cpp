#include "Container.h"

Container::Container()
{

}

Container::~Container()
{
	delete logger;
	delete input;
}

void Container::init()
{
	if (initialized) {
		return;
	}

	logger = new ConsoleLogger();
	input = new Input();
	initialized = true;
}

Logger *Container::get_logger()
{
	return this->logger;
}

Input *Container::get_input()
{
	return this->input;
}

void lua::container::add(lua_State *L)
{
	lua::config::add(L);
	lua::logger::add(app_container.get_logger(), L);
	lua::input::add(app_container.get_input(), L);
}