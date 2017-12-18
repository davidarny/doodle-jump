#include "Doodler.h"
#include "EventLoop.h"

EventLoop::EventLoop(sf::RenderWindow &window, sf::Clock &clock, KeyboardState &keyboardState)
    : m_window(window), m_clock(clock), m_keyboardState(keyboardState) {}

void EventLoop::createWindow() const
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close, settings);
    m_window.setFramerateLimit(MAX_FPS);
}

EventLoop &EventLoop::pollEvents()
{
    m_deltaTime = m_clock.restart().asSeconds();
    sf::Event event{};
    while (m_window.pollEvent(event))
    {
        m_keyboardState.onKeyEventHandler(event);
        onWindowEventHandler(event);
    }
    return *this;
}

EventLoop &EventLoop::redrawFrame(const Entities &entities)
{
    m_window.clear(sf::Color::White);
    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_item) -> void {
        m_window.draw(*p_item);
    });
    m_window.display();
    return *this;
}

EventLoop &EventLoop::init()
{
    createWindow();
    return *this;
}

EventLoop &EventLoop::update(const Entities &entities)
{
    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_item) -> void {
        p_item->updatePosition(m_deltaTime);
    });
    return *this;
}

// TODO: create GameState class and dispatch this stuff there
void EventLoop::onWindowEventHandler(const sf::Event &event)
{
    if (event.type != sf::Event::Closed)
    {
        return;
    }
    m_window.close();
}
