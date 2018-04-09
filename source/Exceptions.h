#ifndef EXCEPTION_H
#define EXCEPTION_H

struct FileNotFoundException : public std::exception {
    const char * what () const throw () {
        return "File Not Found";
    }
};

#endif // EXCEPTION_H
