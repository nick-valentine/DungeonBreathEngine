#ifndef CONTAINER_H
#define CONTAINER_H

#include "ConfigLoader.h"
#include "StringProvider.h"
#include "Logger.h"
#include "DevConsole.h"
#include "DevConsoleLogger.h"
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
        DevConsole *get_console();
    private:
        bool initialized = false;
        Logger * logger;
        Input *input;
        DevConsole *console;
    };

    // Global container instance
    extern Container app_container;
}


#endif //CONTAINER_H
