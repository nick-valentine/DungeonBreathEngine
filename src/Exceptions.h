#ifndef EXCEPTION_H
#define EXCEPTION_H

struct FileNotFoundException : public std::exception {
    const char * what () const throw () {
        return "File Not Found";
    }
};

struct FileNotWriteableException : public std::exception {
    const char * what () const throw () {
        return "File Not Writable";
    }
};

struct FileNotReadableException : public std::exception {
    const char * what () const throw () {
        return "File Not Readable";
    }
};

struct InvalidConfigException : public std::exception {
    const char * what () const throw () {
        return "Invalid Config";
    }
};

struct UnavailableActorException : public std::exception {
    const char * what() const throw () {
        return "Actor Not Available";
    }
};

#endif // EXCEPTION_H
