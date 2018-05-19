#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

#include "Macros.h"

#include "ConfigLoader.h"
#include "Logger.h"
#include  "Input.h"

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

class Script
{
public:
	Script(std::string filename, Input *input, Logger *logger);
	~Script();

	void call();
	/* assumes that the table is at the stack top */
	std::string get_field(std::string key);

	std::string name;
	lua_State * s;
};



#endif //SCRIPT_H