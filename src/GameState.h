#ifndef DOODLE_JUMP_GAMESTATE_H
#define DOODLE_JUMP_GAMESTATE_H

#include "IState.h"

class GameState : public IState
{
public:
    explicit GameState(sf::RenderWindow &window);

    void eventHandler(const sf::Event &event) override;

    State getState() const;

    void setState(State state);

    float getScore() const;

    void setScore(float nextScore);

    void resetScore();

private:
    sf::RenderWindow &m_window;

    float m_score{0.f};

    State m_state{State::MainMenu};

    float positionToScore(float position);
};

#endif //DOODLE_JUMP_GAMESTATE_H
