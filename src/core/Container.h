#ifndef CONTAINER_H
#define CONTAINER_H

#include "ConfigLoader.h"
#include "StringProvider.h"
#include "Logger.h"
#include "ConsoleLogger.h"
#include  "Input.h"

namespace core {
    // Container for global stateless services
    class Container
    {
    public:
        Container();
        ~Container();
        void init();

        Logger *get_logger();
        Input *get_input();
    private:
        bool initialized = false;
        Logger * logger;
        Input *input;
    };

    // Global container instance
    extern Container app_container;
}


#endif //CONTAINER_H
