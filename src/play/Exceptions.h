#ifndef PLAY_EXCEPTION_H
#define PLAY_EXCEPTION_H

namespace play {
    struct UnavailableActorException : public std::exception {
        const char * what() const throw () {
            return "Actor Not Available";
        }
    };
}

#endif // PLAY_EXCEPTION_H
