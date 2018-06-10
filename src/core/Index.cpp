#include "Index.h"

namespace core {
    Index::Index(std::string path)
    {
        filename = path + "/index.txt";
        std::ifstream ifile(filename.c_str());

        std::string temp;

        ifile>>temp;
        while (ifile.good()) {
            entries.insert(temp);
            ifile>>temp;
        }

        ifile.close();
    }

    void Index::add(std::string entry)
    {
        entries.insert(entry);
    }

    void Index::remove(std::string entry)
    {
        entries.erase(entry);
    }

    void Index::save()
    {
        std::ofstream ofile(filename.c_str());

        for (const auto &i : entries) {
            ofile<<i<<"\n";
        }

        ofile.close();
    }

    std::set<std::string> Index::get() const
    {
        return this->entries;
    }
};
