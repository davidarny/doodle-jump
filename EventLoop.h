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
    EventLoop(const std::shared_ptr<KeyboardState> &p_keyboardState, const std::shared_ptr<View> &p_view);

    ~EventLoop() = default;

    void init();

    void pollEvents();

    void update(const Entities &entities);

    void redrawFrame(const Entities &entities);

    const sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;

    const std::shared_ptr<KeyboardState> &m_p_keyboardState;
    const std::shared_ptr<View> &m_p_view;

    float m_deltaTime = 0.f;

    void createWindow();

    void onWindowEventHandler(const sf::Event &event);

};

#endif //DOODLE_JUMP_EVENTLOOP_H
