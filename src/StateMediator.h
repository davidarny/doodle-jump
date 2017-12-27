#ifndef DOODLE_JUMP_STATEMEDIATOR_H
#define DOODLE_JUMP_STATEMEDIATOR_H

#include <variant>
#include "enums.h"
#include "IState.h"
#include "GameState.h"
#include "KeyboardState.h"

class StateMediator
{
public:
    explicit StateMediator(sf::RenderWindow &window);

    const KeysMap &getKeysMap() const;

    const State &getGameState() const;

    void triggerEventHandler(const sf::Event &event);

private:
    sf::RenderWindow &m_window;

    KeyboardState m_keyboardState{KeyboardState()};
    GameState m_gameState = GameState(m_window);

};

#endif //DOODLE_JUMP_STATEMEDIATOR_H
