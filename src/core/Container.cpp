#include "Container.h"

namespace core {
    Container::Container()
    {

    }

    Container::~Container()
    {
        delete logger;
        delete input;
        delete console;
    }

    void Container::init()
    {
        if (initialized) {
            return;
        }

        logger = new DevConsoleLogger();
        input = new Input();
        console = new DevConsole();
        initialized = true;
    }

    Logger *Container::get_logger()
    {
        return this->logger;
    }

    Input *Container::get_input()
    {
        return this->input;
    }

    DevConsole *Container::get_console()
    {
        return this->console;
    }
};

