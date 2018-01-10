#ifndef DOODLE_JUMP_ENUMS_H
#define DOODLE_JUMP_ENUMS_H

#include <cstdlib>

enum class EState : size_t
{
    MAIN_MENU = 0,
    PAUSE_MENU,
    GAME_OVER,
    GAME_PROCESS
};

enum class EType : size_t
{
    PLATFORM_DEFAULT = 0,
    PLATFORM_BONUS_SPRING,
    PLATFORM_BONUS_TRAMPOLINE,
    DOODLER,
    SPRITE
};

#endif //DOODLE_JUMP_ENUMS_H
