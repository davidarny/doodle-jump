#include "KeyboardState.h"

KeyboardState::KeyboardState()
{
    m_keysMap[sf::Keyboard::Left] = false;
    m_keysMap[sf::Keyboard::Right] = false;
}

void KeyboardState::onKeyEventHandler(const sf::Event &event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            onLeftKeyPressed(event.key.code);
            onRightKeyPressed(event.key.code);
            break;
        case sf::Event::KeyReleased:
            onLeftKeyReleased(event.key.code);
            onRightKeyReleased(event.key.code);
            break;
        default:
            break;
    }
}

void KeyboardState::onLeftKeyPressed(const sf::Keyboard::Key &key)
{
    if (key != sf::Keyboard::Left)
    {
        return;
    }
    m_keysMap[sf::Keyboard::Left] = true;
}

void KeyboardState::onRightKeyPressed(const sf::Keyboard::Key &key)
{
    if (key != sf::Keyboard::Right)
    {
        return;
    }
    m_keysMap[sf::Keyboard::Right] = true;
}

const KeysMap &KeyboardState::getKeysMap() const
{
    return m_keysMap;
}

void KeyboardState::onLeftKeyReleased(const sf::Keyboard::Key &key)
{
    if (key != sf::Keyboard::Left)
    {
        return;
    }
    m_keysMap[sf::Keyboard::Left] = false;
}

void KeyboardState::onRightKeyReleased(const sf::Keyboard::Key &key)
{
    if (key != sf::Keyboard::Right)
    {
        return;
    }
    m_keysMap[sf::Keyboard::Right] = false;
}
