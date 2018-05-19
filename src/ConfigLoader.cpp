#include "ConfigLoader.h"

#include <iostream>

const std::string ConfigLoader::config_path = "./GameData/config.txt";
const std::string ConfigLoader::version_path = "./GameData/version.txt";
std::map<std::string, std::string> ConfigLoader::configuration = std::map<std::string, std::string>();
std::string ConfigLoader::version = std::string();

ConfigLoader::ConfigLoader()
{

}

ConfigLoader::~ConfigLoader()
{

} 

void ConfigLoader::load()
{
    std::ifstream ifile;
    ifile.open(ConfigLoader::config_path.c_str());
    while (ifile.good()) {
        std::string key, value;
        ifile>>key>>value;
        configuration[key] = value;
    }
    ifile.close();

    ifile.open(ConfigLoader::version_path.c_str());
    while (ifile.good()) {
        ifile>>version;
    }
    ifile.close();
}

void ConfigLoader::save()
{
    std::ofstream ofile;
    ofile.open(ConfigLoader::config_path.c_str());
    for (c_iter it = ConfigLoader::configuration.begin(); it != ConfigLoader::configuration.end(); ++it) {
        ofile<<it->first<<" "<<it->second<<"\n";
    }
    ofile.close();
}

std::string ConfigLoader::get_version()
{
    return version;
}

int ConfigLoader::get_int_option(std::string key, int default_to)
{
    std::stringstream dss;
    dss<<default_to;
    std::string value = ConfigLoader::get_string_option(key, dss.str());
    std::stringstream ss;
    ss.str(value);
    int x;
    ss>>x;
    return x;
}

std::string ConfigLoader::get_string_option(std::string key, std::string default_to)
{
    c_iter it = ConfigLoader::configuration.find(key);
    if (it != ConfigLoader::configuration.end()) {
        return it->second;
    } else {
        if (default_to != "-1") {
            ConfigLoader::mutate_option(key, default_to);
            ConfigLoader::save();
        }
        return default_to;
    }
}

void ConfigLoader::mutate_option(std::string key, int value)
{
    std::stringstream ss;
    std::string s;
    ss<<value;
    s = ss.str();
    ConfigLoader::mutate_option(key, s);
}

void ConfigLoader::mutate_option(std::string key, std::string value)
{
    ConfigLoader::configuration[key] = value;
}

std::vector< std::pair<std::string, std::string> > ConfigLoader::get_all_options()
{
    std::vector< std::pair<std::string, std::string> > options;
    for (c_iter it = ConfigLoader::configuration.begin(); it != ConfigLoader::configuration.end(); ++it) {
        options.push_back(*it);
    }
    return options;
}

void lua::config::add(lua_State *L)
{
	static const struct luaL_Reg mylib[] = {
		{"get_int", get_int},
		{"get_string", get_string},
		{"set", set},
		{"save", save},
		{NULL, NULL}
	};
	lua_getglobal(L, "config");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
	}
	luaL_setfuncs(L, mylib, 0);
	lua_setglobal(L, "config");
}

int lua::config::get_int(lua_State *L)
{
	if (!lua_isstring(L, -2)) {
		error(L, "config.get_int arg 1 not string");
	}
	auto c = lua_tostring(L, -2);
	if (!lua_isnumber(L, -1)) {
		error(L, "config.get_int arg 2 not int");
	}
	auto d = lua_tonumber(L, -1);

	int n = ConfigLoader::get_int_option(c, d);

	lua_pushnumber(L, n);

	return 1;
}

int lua::config::get_string(lua_State *L)
{
	if (!lua_isstring(L, -2)) {
		error(L, "config.get_string arg 1 not string");
	}
	auto c = lua_tostring(L, -2);
	if (!lua_isstring(L, -1)) {
		error(L, "config.get_string arg 2 not string");
	}
	auto d = lua_tostring(L, -1);

	auto s = ConfigLoader::get_string_option(c, d);

	lua_pushstring(L, s.c_str());

	return 1;
}

int lua::config::set(lua_State *L)
{
	if (!lua_isstring(L, -2)) {
		error(L, "config.set arg 1 not string");
	}
	auto c = lua_tostring(L, -2);
	if (lua_isnumber(L, -1)) {
		auto d = lua_tonumber(L, -1);
		ConfigLoader::mutate_option(c, d);
		return 0;
	} else if (lua_isstring(L, -1)) {
		auto d = lua_tostring(L, -1);
		ConfigLoader::mutate_option(c, d);
		return 0;
	} else {
		error(L, "config.set arg 2 not int or string");
	}
	return -1;
}

int lua::config::save(lua_State *L)
{
	ConfigLoader::save();
	return 0;
}