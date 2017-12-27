#ifndef DOODLE_JUMP_GAMESTATE_H
#define DOODLE_JUMP_GAMESTATE_H

#include "IState.h"

class GameState : public IState
{
public:
    explicit GameState(sf::RenderWindow &window);

    void eventHandler(const sf::Event &event) override;

    const State &getState() const;

private:
    sf::RenderWindow &m_window;

    State m_state{State::MainMenu};
};

#endif //DOODLE_JUMP_GAMESTATE_H
