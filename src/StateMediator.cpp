#include "StateMediator.h"

StateMediator::StateMediator(sf::RenderWindow &window) : m_window(window) {}

const KeysMap &StateMediator::getKeysMap() const
{
    return m_keyboardState.getKeysMap();
}

State StateMediator::getGameState() const
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
