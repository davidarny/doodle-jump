#include <SFML/Graphics.hpp>
#include <memory>
#include "EventLoop.h"
#include "Doodler.h"
#include "Platform.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    sf::RenderWindow window;
    sf::Clock clock;

    Entities entities;

    EventLoop eventLoop(window, clock);
    eventLoop.init();

    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        std::shared_ptr<Platform> p_platform = std::make_shared<Platform>(Platform());
        entities.push_back(p_platform);
    }

    std::shared_ptr<Doodler> p_doodler = std::make_shared<Doodler>(Doodler());

    entities.push_back(p_doodler);

    while (window.isOpen())
    {
        eventLoop
            .pollEvents(p_doodler)
            .update(entities)
            .redrawFrame(entities);
    }
}
