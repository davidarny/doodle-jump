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
#include "Engine.h"
#include "Overlay.h"
#include "Sprite.h"
#include "Assets.h"

class EventLoop
{
public:
    EventLoop() = default;

    void pollEvents();

    void update();

    void redrawFrame();

    void init();

    const sf::RenderWindow &getWindow() const;

private:
    Sprite m_backgroundSprite = Sprite(SpriteOptions{Assets::BACKGROUND.length,
                                                     Assets::BACKGROUND.data,
                                                     {0.f, BACKGROUND_SIZE.y},
                                                     BACKGROUND_SCALE,
                                                     false,
                                                     true});
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Engine m_engine;
    View m_view;
    StateMediator m_stateMediator{StateMediator(m_window)};
    Menu m_menu{Menu(m_stateMediator)};
    Overlay m_overlay{Overlay(m_stateMediator)};
    Entities m_entities;

    std::shared_ptr<IEntity> m_p_doodler;

    float m_deltaTime = 0.f;

    void createWindow();

    void drawGameScreen();

    void drawMenuScreen();

    void restart();

};

#endif //DOODLE_JUMP_EVENTLOOP_H
