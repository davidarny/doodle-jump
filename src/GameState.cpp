#include "GameState.h"

void GameState::eventHandler(const sf::Event &event)
{
    if (event.type != sf::Event::Closed)
    {
        return;
    }
    m_window.close();
}

GameState::GameState(sf::RenderWindow &window) : m_window(window) {}

State GameState::getState() const
{
    return m_state;
}

void GameState::setState(const State state)
{
    m_state = state;
}


