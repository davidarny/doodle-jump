#include <SFML/Graphics.hpp>
#include <iostream>
#include "EventLoop.h"

bool IS_DEBUG = false;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        const std::string arg = argv[1];
        if (arg == "--help")
        {
            std::cout << "Usage: doodle-jump [<option(s)>]\n"
                      << "Options:\n"
                      << "  --help: show help information\n"
                      << "  --debug: enable debug mode (shows hitboxes)\n\n"
                      << "For bug reporting, please make issue:\n"
                      << "<https://github.com/DavidArutiunian/doodle-jump/issues>"
                      << std::endl;
            return EXIT_SUCCESS;
        }
        if (arg == "--debug")
        {
            IS_DEBUG = true;
        }
    }

    srand((unsigned) time(nullptr));

    EventLoop eventLoop;

    eventLoop.init();

    while (eventLoop.getWindow().isOpen())
    {
        eventLoop.pollEvents();
        eventLoop.update();
        eventLoop.redrawFrame();
    }

    return EXIT_SUCCESS;
}
