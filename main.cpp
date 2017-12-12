#include <SFML/Graphics.hpp>
#include "EventLoop.h"

int main()
{
    sf::RenderWindow window;
    sf::Clock clock;

    EventLoop eventLoop(window, clock);
    eventLoop.init();

    while (window.isOpen())
    {
        eventLoop
            .pollEvents()
            .update()
            .redrawFrame({});
    }

    return 0;
}
