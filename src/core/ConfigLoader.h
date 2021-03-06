#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <iostream>

namespace core {
    /**
     * Configuration Loader.
     * Loads and manages Configuration.
     */
    class ConfigLoader
    {
    public:
        static void load();
        static void save();

        static std::string get_version();

        static int get_int_option(std::string key, int default_to = -1);
        static std::string get_string_option(std::string key, std::string default_to = "");

        static void mutate_option(std::string key, int value);
        static void mutate_option(std::string key, std::string value);

        static std::vector< std::pair<std::string, std::string> > get_all_options();
    private:
        typedef std::map<std::string, std::string>::iterator c_iter;

        ConfigLoader();
        ~ConfigLoader();

        static const std::string config_path;
        static const std::string version_path;

        /**
         * map of key to value
         */
        static std::map<std::string, std::string> configuration;

        static std::string version;
    };
};

#endif // CONFIGLOADER_H
