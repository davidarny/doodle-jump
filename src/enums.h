#ifndef DOODLE_JUMP_ENUMS_H
#define DOODLE_JUMP_ENUMS_H

#include <cstdlib>

enum class State : size_t
{
    MainMenu = 0,
    PauseMenu,
    GameOver,
    Game
};

enum class EntityType : size_t
{
    Platform = 0,
    PlatformWithSpring,
    PlatformWithTrampoline,
    Doodler,
    Sprite
};

#endif //DOODLE_JUMP_ENUMS_H
