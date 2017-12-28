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
    EventLoop(const View &view,
              sf::RenderWindow &window,
              StateMediator &stateMediator,
              Menu &menu,
              Entities &entities);

    void init();

    void pollEvents();

    void update();

    void redrawFrame();

    const sf::RenderWindow &getWindow() const;

private:
    const View &m_view;
    sf::RenderWindow &m_window;

    sf::Clock m_clock;

    StateMediator &m_stateMediator;
    Menu &m_menu;

    Entities &m_entities;

    float m_deltaTime = 0.f;

    void createWindow();

    void drawGameScreen();

    void drawMenuScreen();

};

#endif //DOODLE_JUMP_EVENTLOOP_H
