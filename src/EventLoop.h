#ifndef DOODLE_JUMP_EVENTLOOP_H
#define DOODLE_JUMP_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "consts.h"
#include "IEntity.h"
#include "KeyboardState.h"
#include "GameState.h"
#include "StateMediator.h"
#include "View.h"
#include "Menu.h"

class EventLoop
{
public:
    EventLoop(const View &view, sf::RenderWindow &window, StateMediator &stateMediator);

    void init();

    void pollEvents();

    void update(const Entities &entities);

    void redrawFrame(const Entities &entities, const Menu &menu);

    const sf::RenderWindow &getWindow() const;

private:
    const View &m_view;
    sf::RenderWindow &m_window;
    sf::Clock m_clock;

    StateMediator &m_stateMediator;

    float m_deltaTime = 0.f;

    void createWindow();

    void drawGameScreen(const Entities &entities);

    void drawMenuScreen(const Menu &menu);

};

#endif //DOODLE_JUMP_EVENTLOOP_H
