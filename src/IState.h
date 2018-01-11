#ifndef DOODLE_JUMP_ISTATE_H
#define DOODLE_JUMP_ISTATE_H

#include <SFML/Graphics.hpp>
#include "enums.h"

class IState
{
public:
    virtual void eventHandler(const sf::Event &event) = 0;
};

#endif //DOODLE_JUMP_ISTATE_H
