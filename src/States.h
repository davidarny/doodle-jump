#ifndef DOODLE_JUMP_STATEMEDIATOR_H
#define DOODLE_JUMP_STATEMEDIATOR_H

#include <variant>
#include "enums.h"
#include "IState.h"
#include "GameState.h"
#include "KeyboardState.h"

class States
{
public:
    explicit States(sf::RenderWindow &window);

    const KeysMap &getKeysMap() const;

    EState getState() const;

    float getScore() const;

    void setState(EState state);

    void setScore(float nextScore);

    void resetScore();

    void triggerEventHandler(const sf::Event &event);

private:
    sf::RenderWindow &m_window;
    KeyboardState m_keyboardState = KeyboardState();
    GameState m_gameState = GameState(m_window);
};

#endif //DOODLE_JUMP_STATEMEDIATOR_H
