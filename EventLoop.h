#ifndef DOODLE_JUMP_EVENTLOOP_H
#define DOODLE_JUMP_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "consts.h"
#include "IEntity.h"
#include "KeyboardState.h"

class EventLoop
{
public:
    EventLoop(sf::RenderWindow &window, sf::Clock &clock, KeyboardState &keyboardState);

    ~EventLoop() = default;

    EventLoop &init();

    EventLoop &pollEvents();

    EventLoop &update(const Entities &entities);

    EventLoop &redrawFrame(const Entities &entities);

private:
    sf::RenderWindow &m_window;
    sf::Clock &m_clock;
    KeyboardState &m_keyboardState;

    float m_deltaTime = 0.f;

    void createWindow() const;

    void onWindowEventHandler(const sf::Event &event);

};

#endif //DOODLE_JUMP_EVENTLOOP_H
