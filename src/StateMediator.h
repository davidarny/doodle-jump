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

    State getState() const;

    float getScore() const;

    void triggerEventHandler(const sf::Event &event);

    void setState(State state);

    void setScore(float nextScore);

private:
    sf::RenderWindow &m_window;

    KeyboardState m_keyboardState{KeyboardState()};
    GameState m_gameState = GameState(m_window);
};

#endif //DOODLE_JUMP_STATEMEDIATOR_H
