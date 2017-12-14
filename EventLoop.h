#ifndef DOODLE_JUMP_EVENTLOOP_H
#define DOODLE_JUMP_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "consts.h"
#include "IEntity.h"

class EventLoop
{
public:
    EventLoop(sf::RenderWindow &window, sf::Clock &clock);

    ~EventLoop() = default;

    EventLoop &init();

    EventLoop &pollEvents(const std::shared_ptr<IEntity> &p_entity);

    EventLoop &update(const Entities &entities);

    EventLoop &redrawFrame(const Entities &entities);

private:
    sf::RenderWindow &m_window;
    sf::Clock &m_clock;

    float m_deltaTime = 0.f;

    void createWindow() const;

};

#endif //DOODLE_JUMP_EVENTLOOP_H
