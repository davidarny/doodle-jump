#include "Doodler.h"
#include "EventLoop.h"
#include "Platform.h"

void EventLoop::update()
{
    const State state = m_stateMediator.getState();
    switch (state)
    {
        case State::Game:
        {
            const float dtPhysics = m_deltaTime / MAX_PRECISION_COUNT;
            for (unsigned i = 0; i < MAX_PRECISION_COUNT; ++i)
            {
                const sf::Vector2f &viewCenter = m_view.getView().getCenter();
                m_backgroundSprite.setPosition({0.f, viewCenter.y});
                m_overlay.updateScorePosition(viewCenter.y);
                m_view.followTo(m_p_doodler);
                for (auto &&m_entity : m_entities)
                {
                    m_entity->updatePosition(dtPhysics);
                }
                m_engine.checkCollision(m_entities);
            }
            m_stateMediator.setScore(m_p_doodler->getPosition().y);
            m_overlay.updateScoreString();
            m_menu.updateScoreString();
            m_engine.addPlatforms(m_entities);
            m_engine.removePlatforms(m_entities);
            break;
        }
        default:
            break;
    }
}

void EventLoop::pollEvents()
{
    m_deltaTime = m_clock.restart().asSeconds();
    sf::Event event{};
    while (m_window.pollEvent(event))
    {
        const sf::Vector2f &mousePosition = sf::Vector2f(sf::Mouse::getPosition(m_window));
        m_p_doodler->eventHandler(event);
        m_stateMediator.triggerEventHandler(event);
        m_menu.eventHandler(event, mousePosition, std::bind(&EventLoop::restart, this));
    }
}

void EventLoop::redrawFrame()
{
    const State state = m_stateMediator.getState();
    switch (state)
    {
        case State::Game:
            drawGameScreen();
            break;
        case State::GameOver:
        case State::MainMenu:
            drawMenuScreen();
            break;
        default:
            break;
    }
}

void EventLoop::drawGameScreen()
{
    m_window.clear(sf::Color::White);
    m_window.setView(m_view.getView());
    m_window.draw(m_backgroundSprite);
    for (auto &&m_entity : m_entities)
    {
        m_window.draw(*m_entity);
    }
    m_window.draw(m_engine);
    m_window.draw(m_overlay);
    m_window.display();
}

void EventLoop::drawMenuScreen()
{
    sf::View &view = m_view.getView();
    view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    m_backgroundSprite.setPosition({0.f, view.getCenter().y});
    m_window.clear(sf::Color::White);
    m_window.setView(view);
    m_window.draw(m_backgroundSprite);
    m_window.draw(m_menu);
    m_window.display();
}

void EventLoop::createWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close, settings);
    m_window.setFramerateLimit(MAX_FPS);
    m_window.requestFocus();

    sf::Image icon;
    if (icon.loadFromMemory(Assets::ICON.data, Assets::ICON.length))
    {
        m_window.setIcon(ICON_IMAGE_SIZE.x, ICON_IMAGE_SIZE.y, icon.getPixelsPtr());
    }
}

const sf::RenderWindow &EventLoop::getWindow() const
{
    return m_window;
}

void EventLoop::init()
{
    if (!m_window.isOpen())
    {
        createWindow();
    }

    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        m_entities.push_back(std::make_shared<Platform>(Platform()));
    }

    m_p_doodler = std::make_shared<Doodler>(Doodler(m_stateMediator));
    m_entities.push_back(m_p_doodler);
}

void EventLoop::restart()
{
    Platform::resetMultiplier();
    m_entities.clear();
    m_stateMediator.resetScore();
    init();
}
