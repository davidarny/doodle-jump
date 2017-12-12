#include <SFML/Graphics.hpp>
#include <memory>
#include "EventLoop.h"
#include "Doodler.h"

int main()
{
    sf::RenderWindow window;
    sf::Clock clock;

    Entities entities;

    EventLoop eventLoop(window, clock);
    eventLoop.init();

    std::shared_ptr<Doodler> p_doodler = std::make_shared<Doodler>(Doodler());

    entities.push_back(p_doodler);

    while (window.isOpen())
    {
        eventLoop
            .pollEvents()
            .update(entities)
            .redrawFrame(entities);
    }
}
