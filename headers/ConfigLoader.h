#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <iostream>

/**
 * Configuration Loader.
 * Loads and manages Configuration.
 */
class ConfigLoader
{
public:
    static void load();
    static void save();

    static std::string getVersion();

    static int getIntOption(std::string key, int defaultTo = -1);
    static std::string getStringOption(std::string key, std::string defaultTo = "");

    static void mutateOption(std::string key, int value);
    static void mutateOption(std::string key, std::string value);

    static std::vector< std::pair<std::string, std::string> > getAllOptions();
private:
    typedef std::map<std::string, std::string>::iterator c_iter;

    ConfigLoader();
    ~ConfigLoader();

    static const std::string configPath;
    static const std::string versionPath;

    /**
     * map of key to value
     */
    static std::map<std::string, std::string> configuration;

    static std::string version;
};

#endif // CONFIGLOADER_H
