#ifndef DOODLE_JUMP_EVENTLOOP_H
#define DOODLE_JUMP_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "consts.h"
#include "Entity.h"

class EventLoop
{
private:
    sf::RenderWindow &m_window;
    sf::Clock &m_clock;

    float m_deltaTime = 0.f;

    void createWindow();

public:
    EventLoop(sf::RenderWindow &window, sf::Clock &clock);

    ~EventLoop() = default;

    EventLoop &init();

    EventLoop &pollEvents();

    EventLoop &update(const Entities &entities);

    EventLoop &redrawFrame(const Entities &entities);
};

#endif //DOODLE_JUMP_EVENTLOOP_H
