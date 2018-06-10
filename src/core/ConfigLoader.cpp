#include "ConfigLoader.h"

namespace core {

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
}

