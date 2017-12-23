#include "Doodler.h"
#include "EventLoop.h"
#include "resources/icon.h"

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
        m_p_keyboardState->onKeyEventHandler(event);
        onWindowEventHandler(event);
    }
}

void EventLoop::redrawFrame(const Entities &entities)
{
    m_window.clear(sf::Color::White);
    m_window.setView(m_p_view->getView());
    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_item) -> void {
        m_window.draw(*p_item);
    });
    m_window.display();
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

// TODO: create GameState class and dispatch this stuff there
void EventLoop::onWindowEventHandler(const sf::Event &event)
{
    if (event.type != sf::Event::Closed)
    {
        return;
    }
    m_window.close();
}

const sf::RenderWindow &EventLoop::getWindow() const
{
    return m_window;
}

EventLoop::EventLoop(const std::shared_ptr<KeyboardState> &p_keyboardState, const std::shared_ptr<View> &p_view)
    : m_p_keyboardState(p_keyboardState), m_p_view(p_view) {}

