#include <SFML/Graphics.hpp>
#include "EventLoop.h"

int main()
{
    srand(time(nullptr));

    EventLoop eventLoop;

    eventLoop.init();

    while (eventLoop.getWindow().isOpen())
    {
        eventLoop.pollEvents();
        eventLoop.update();
        eventLoop.redrawFrame();
    }
}
