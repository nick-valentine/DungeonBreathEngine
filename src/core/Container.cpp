#include "Container.h"

namespace core {
    Container::Container()
    {

    }

    Container::~Container()
    {
        delete logger;
        delete input;
    }

    void Container::init()
    {
        if (initialized) {
            return;
        }

        logger = new ConsoleLogger();
        input = new Input();
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
};

