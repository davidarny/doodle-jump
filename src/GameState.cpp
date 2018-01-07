#include "GameState.h"
#include "consts.h"

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

void GameState::setScore(const float nextScore)
{
    const float buffer = positionToScore(nextScore);
    if (buffer <= m_score)
    {
        return;
    }
    m_score = buffer;
}

float GameState::getScore() const
{
    return m_score;
}

float GameState::positionToScore(const float position)
{
    if (position > 0)
    {
        return static_cast<float>(WINDOW_HEIGHT) - std::abs(position);
    } else
    {
        return static_cast<float>(WINDOW_HEIGHT) + std::abs(position);
    }
}

void GameState::resetScore()
{
    m_score = 0.f;
}
