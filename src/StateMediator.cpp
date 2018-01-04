#include "StateMediator.h"

StateMediator::StateMediator(sf::RenderWindow &window) : m_window(window) {}

const KeysMap &StateMediator::getKeysMap() const
{
    return m_keyboardState.getKeysMap();
}

State StateMediator::getState() const
{
    return m_gameState.getState();
}

void StateMediator::triggerEventHandler(const sf::Event &event)
{
    m_gameState.eventHandler(event);
    m_keyboardState.eventHandler(event);
}

void StateMediator::setState(const State state)
{
    m_gameState.setState(state);
}

void StateMediator::setScore(const float nextScore)
{
    m_gameState.setScore(nextScore);
}

float StateMediator::getScore() const
{
    return m_gameState.getScore();
}
