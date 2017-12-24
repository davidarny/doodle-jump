#ifndef DOODLE_JUMP_KEYBOARDSTATE_H
#define DOODLE_JUMP_KEYBOARDSTATE_H

#include <SFML/Graphics.hpp>
#include "IState.h"

using KeysMap = std::map<sf::Keyboard::Key, bool>;

class KeyboardState : public IState
{
public:
    KeyboardState();

    void eventHandler(const sf::Event &event) override;

    const KeysMap &getKeysMap() const;

private:
    KeysMap m_keysMap;

    void onLeftKeyPressed(const sf::Keyboard::Key &key);

    void onRightKeyPressed(const sf::Keyboard::Key &key);

    void onLeftKeyReleased(const sf::Keyboard::Key &key);

    void onRightKeyReleased(const sf::Keyboard::Key &key);
};

#endif //DOODLE_JUMP_KEYBOARDSTATE_H
