#include <SFML/Graphics.hpp>
#include <memory>
#include "Engine.h"
#include "EventLoop.h"
#include "Platform.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    sf::RenderWindow window;
    sf::Clock clock;

    Entities entities;

    KeyboardState keyboardState;

    EventLoop eventLoop(window, clock, keyboardState);
    eventLoop.init();

    Engine engine;

    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        std::shared_ptr<Platform> p_platform = std::make_shared<Platform>(Platform());
        entities.push_back(p_platform);
    }

    std::shared_ptr<Doodler> p_doodler = std::make_shared<Doodler>(Doodler(keyboardState));

    entities.push_back(p_doodler);

    while (window.isOpen())
    {
        eventLoop.pollEvents();
        eventLoop.update(entities);
        engine.checkCollision(entities);
        eventLoop.redrawFrame(entities);
    }
}
