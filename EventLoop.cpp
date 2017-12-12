#include "EventLoop.h"

EventLoop::EventLoop(sf::RenderWindow &window, sf::Clock &clock) : m_window(window), m_clock(clock) {}

void EventLoop::createWindow()
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
        switch (event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Left:
                        break;
                    case sf::Keyboard::Right:
                        break;
                    default:
                        break;
                }
                break;
            }
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                    case sf::Keyboard::Left:
                    case sf::Keyboard::Right:
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return *this;
}

EventLoop &EventLoop::redrawFrame(const Entities &entities)
{
    m_window.clear(sf::Color::White);
    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<Entity> p_item) -> void {
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
    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<Entity> p_item) -> void {
        p_item->updatePosition(m_deltaTime);
    });
    return *this;
}
