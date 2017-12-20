#ifndef DOODLE_JUMP_EVENTLOOP_H
#define DOODLE_JUMP_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "consts.h"
#include "IEntity.h"
#include "KeyboardState.h"
#include "View.h"

class EventLoop
{
public:
    ~EventLoop() = default;

    void init();

    void pollEvents();

    void update(const Entities &entities);

    void redrawFrame(const Entities &entities);

    void addKeyboardState(std::shared_ptr<KeyboardState> p_keyboardState);

    void addView(std::shared_ptr<View> p_view);

    const sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;

    std::shared_ptr<KeyboardState> p_m_keyboardState;
    std::shared_ptr<View> p_m_view;

    float m_deltaTime = 0.f;

    void createWindow();

    void onWindowEventHandler(const sf::Event &event);

};

#endif //DOODLE_JUMP_EVENTLOOP_H
