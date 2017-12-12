#ifndef DOODLE_JUMP_EVENTLOOP_H
#define DOODLE_JUMP_EVENTLOOP_H

#include <SFML/Graphics.hpp>
#include "consts.h"

class EventLoop
{
private:
    sf::RenderWindow &m_window;
    const sf::Clock &m_clock;

    void createWindow();

public:
    EventLoop(sf::RenderWindow &window, const sf::Clock &clock);

    ~EventLoop() = default;

    EventLoop &init();

    EventLoop &pollEvents();

    EventLoop &update();

    EventLoop &redrawFrame(const std::vector<sf::Drawable> &drawable);
};

#endif //DOODLE_JUMP_EVENTLOOP_H
