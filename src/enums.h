#ifndef DOODLE_JUMP_ENUMS_H
#define DOODLE_JUMP_ENUMS_H

#include <cstdlib>

enum class State : size_t
{
    MainMenu = 0,
    PauseMenu,
    Game
};

enum class StateType : size_t
{
    Game = 0,
    Keyboard
};

enum class EntityType : size_t
{
    Platform = 0,
    Doodler
};

#endif //DOODLE_JUMP_ENUMS_H
