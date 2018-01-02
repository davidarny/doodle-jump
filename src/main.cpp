#include <SFML/Graphics.hpp>
#include <memory>
#include "View.h"
#include "Engine.h"
#include "EventLoop.h"
#include "Platform.h"

int main()
{
    srand(time(nullptr));

    sf::RenderWindow window;
    StateMediator stateMediator(window);

    Menu menu(stateMediator);
    Engine engine;
    View view;
    Entities entities;

    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        std::shared_ptr<Platform> p_platform = std::make_shared<Platform>(Platform());
        entities.push_back(p_platform);
    }

    std::shared_ptr<Doodler> p_doodler = std::make_shared<Doodler>(Doodler(stateMediator));
    entities.push_back(p_doodler);

    EventLoop eventLoop(view, window, stateMediator, menu, entities);

    eventLoop.init();

    while (eventLoop.getWindow().isOpen())
    {
        view.followTo(p_doodler);
        eventLoop.pollEvents();
        eventLoop.update();
        engine.checkCollision(entities);
        engine.addPlatforms(entities);
        engine.removePlatforms(entities);
        eventLoop.redrawFrame();
    }
}
