#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include <string>
#include <set>

class Index
{
public:
    Index(std::string path);

    void add(std::string entry);
    void remove(std::string entry);
    void save();

    std::set<std::string> get() const;
private:
    std::string filename;
    std::set<std::string> entries;
};

#endif  //INDEX_H
