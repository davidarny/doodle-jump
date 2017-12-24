#ifndef DOODLE_JUMP_EVENTLOOP_H
#define DOODLE_JUMP_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "consts.h"
#include "IEntity.h"
#include "KeyboardState.h"
#include "GameState.h"
#include "View.h"

class EventLoop
{
public:
    EventLoop(const View &view, sf::RenderWindow &window, const States &states);

    void init();

    void pollEvents();

    void update(const Entities &entities);

    void redrawFrame(const Entities &entities);

    const sf::RenderWindow &getWindow() const;

private:
    const View &m_view;
    sf::RenderWindow &m_window;
    sf::Clock m_clock;

    const States &m_states;

    float m_deltaTime = 0.f;

    void createWindow();

};

#endif //DOODLE_JUMP_EVENTLOOP_H
