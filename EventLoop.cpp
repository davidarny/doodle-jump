#include "EventLoop.h"

EventLoop::EventLoop(sf::RenderWindow &window, const sf::Clock &clock) : m_window(window), m_clock(clock) {}

void EventLoop::createWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close, settings);
    m_window.setFramerateLimit(MAX_FPS);
}

EventLoop &EventLoop::pollEvents()
{
    sf::Event event{};
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseMoved:
                break;
            default:
                break;
        }
    }
    return *this;
}

EventLoop &EventLoop::redrawFrame(const std::vector<sf::Drawable> &drawable)
{
    m_window.clear(sf::Color::White);
    std::for_each(drawable.begin(), drawable.end(), [&](const sf::Drawable &item) -> void {
        m_window.draw(item);
    });
    m_window.display();
    return *this;
}

EventLoop &EventLoop::init()
{
    createWindow();
    return *this;
}

EventLoop &EventLoop::update()
{
    return *this;
}
