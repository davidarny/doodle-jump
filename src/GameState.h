#ifndef DOODLE_JUMP_GAMESTATE_H
#define DOODLE_JUMP_GAMESTATE_H

#include "IState.h"

class GameState : public IState
{
public:
    explicit GameState(sf::RenderWindow &window);

    void eventHandler(const sf::Event &event) override;

    EState getState() const;

    void setState(EState state);

    float getScore() const;

    void setScore(float nextScore);

    void resetScore();

private:
    float m_score = 0.f;
    sf::RenderWindow &m_window;
    EState m_state = EState::MAIN_MENU;

    float positionToScore(float position);
};

#endif //DOODLE_JUMP_GAMESTATE_H
