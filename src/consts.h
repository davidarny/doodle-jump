#ifndef DOODLE_JUMP_CONSTS_H
#define DOODLE_JUMP_CONSTS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <memory>

/// Window params
static const unsigned WINDOW_WIDTH = 400;
static const unsigned WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Doodle Jump";
static const unsigned ANTIALIASING_LEVEL = 8;
static const unsigned MAX_FPS = 60;

/// Game params
static const float G = 9.8f;
static const float TIME_ACCELERATOR = 6.5f;
static const float MOVE_SPEED = 350.f;
static const size_t PLATFORM_COUNT = 18;
static const float DOODLER_SPEED = 65.f;
static const unsigned MAX_PRECISION_COUNT = 16;
static const float DEAD_TIME = 3.5f;
static const float SCORE_MULTIPLIER = 0.1f;
static const float COLLISION_TOLERANCE = 2.f;

/// Menu params
static const unsigned BASE_MARGIN = 20;
static const unsigned LOGO_TEXT_SIZE = 50;
static const unsigned SCORE_TEXT_SIZE = 30;
static const unsigned GAME_SCORE_TEXT_SIZE = 20;

/// Debug params
extern bool IS_DEBUG;

#endif //DOODLE_JUMP_CONSTS_H
