#include "Doodler.h"
#include "EventLoop.h"
#include "icon.h"

void EventLoop::createWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close, settings);
    m_window.setFramerateLimit(MAX_FPS);

    sf::Image icon;
    if (icon.loadFromMemory(ICON_IMAGE.data, std::size(ICON_IMAGE.data)))
    {
        m_window.setIcon(ICON_IMAGE.width, ICON_IMAGE.height, icon.getPixelsPtr());
    }
}

void EventLoop::pollEvents()
{
    m_deltaTime = m_clock.restart().asSeconds();
    sf::Event event{};
    while (m_window.pollEvent(event))
    {
        m_stateMediator.triggerEventHandler(event);
    }
}

void EventLoop::redrawFrame(const Entities &entities, const Menu &menu)
{
    const State &state = m_stateMediator.getGameState();
    switch (state)
    {
        case State::Game:
            drawGameScreen(entities);
            break;
        case State::MainMenu:
            drawMenuScreen(menu);
            break;
        default:
            break;
    }

}

void EventLoop::init()
{
    createWindow();
}

void EventLoop::update(const Entities &entities)
{
    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_item) -> void {
        p_item->updatePosition(m_deltaTime);
    });
}

const sf::RenderWindow &EventLoop::getWindow() const
{
    return m_window;
}

EventLoop::EventLoop(const View &view, sf::RenderWindow &window, StateMediator &stateMediator)
    : m_view(view), m_window(window), m_stateMediator(stateMediator) {}

void EventLoop::drawGameScreen(const Entities &entities)
{
    m_window.clear(sf::Color::White);
    m_window.setView(m_view.getView());
    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_item) -> void {
        m_window.draw(*p_item);
    });
    m_window.display();
}

void EventLoop::drawMenuScreen(const Menu &menu)
{
    m_window.clear(sf::Color::White);
    m_window.draw(menu);
    m_window.display();
}

