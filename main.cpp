#include <SFML/Graphics.hpp>
#include <memory>
#include "View.h"
#include "Engine.h"
#include "EventLoop.h"
#include "Platform.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    Entities entities;
    Engine engine;
    EventLoop eventLoop;

    std::shared_ptr<KeyboardState> p_keyboardState = std::make_shared<KeyboardState>(KeyboardState());
    std::shared_ptr<View> p_view = std::make_shared<View>(View());

    eventLoop.init();
    eventLoop.addView(p_view);
    eventLoop.addKeyboardState(p_keyboardState);

    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        std::shared_ptr<Platform> p_platform = std::make_shared<Platform>(Platform());
        entities.push_back(p_platform);
    }

    std::shared_ptr<Doodler> p_doodler = std::make_shared<Doodler>(Doodler());
    p_doodler->addKeyboardState(p_keyboardState);
    entities.push_back(p_doodler);

    p_view->followTo(p_doodler);

    while (eventLoop.getWindow().isOpen())
    {
        eventLoop.pollEvents();
        eventLoop.update(entities);
        engine.checkCollision(entities);
        eventLoop.redrawFrame(entities);
    }
}
