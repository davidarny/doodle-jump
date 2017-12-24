#include <SFML/Graphics.hpp>
#include <memory>
#include "View.h"
#include "Engine.h"
#include "EventLoop.h"
#include "Platform.h"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    sf::RenderWindow window;

    std::shared_ptr<KeyboardState> p_keyboardState = std::make_shared<KeyboardState>(KeyboardState());
    std::shared_ptr<GameState> p_gameState = std::make_shared<GameState>(GameState(window));

    States states;
    states[StateType::Game] = p_gameState;
    states[StateType::Keyboard] = p_keyboardState;

    Entities entities;
    Engine engine;
    View view;
    EventLoop eventLoop(view, window, states);

    eventLoop.init();

    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        std::shared_ptr<Platform> p_platform = std::make_shared<Platform>(Platform());
        entities.push_back(p_platform);
    }

    std::shared_ptr<Doodler> p_doodler = std::make_shared<Doodler>(Doodler(p_keyboardState));
    entities.push_back(p_doodler);

    while (eventLoop.getWindow().isOpen())
    {
        view.followTo(p_doodler);
        eventLoop.pollEvents();
        eventLoop.update(entities);
        engine.checkCollision(entities);
        eventLoop.redrawFrame(entities);
    }
}
