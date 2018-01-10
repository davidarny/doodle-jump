#include "States.h"

States::States(sf::RenderWindow &window) : m_window(window) {}

const KeysMap &States::getKeysMap() const
{
    return m_keyboardState.getKeysMap();
}

EState States::getState() const
{
    return m_gameState.getState();
}

void States::triggerEventHandler(const sf::Event &event)
{
    m_gameState.eventHandler(event);
    m_keyboardState.eventHandler(event);
}

void States::setState(const EState state)
{
    m_gameState.setState(state);
}

void States::setScore(const float nextScore)
{
    m_gameState.setScore(nextScore);
}

float States::getScore() const
{
    return m_gameState.getScore();
}

void States::resetScore()
{
    m_gameState.resetScore();
}
