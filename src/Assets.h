#ifndef DOODLE_JUMP_ASSETS_H
#define DOODLE_JUMP_ASSETS_H
#define INCBIN_PREFIX
#define INCBIN_STYLE INCBIN_STYLE_SNAKE

#include <SFML/Graphics.hpp>
#include "../lib/incbin/incbin.h"

// TODO: redesign texture scaling

static const unsigned ICON_SIZE = 32;
static const sf::Vector2f BACKGROUND_SIZE = {640.f, 1024.f};
static const sf::Vector2f BACKGROUND_SCALE = {1.f, 1.f};
static const sf::Vector2f DOODLER_SIZE = {93.f, 83.f};
static const sf::Vector2f DOODLER_SCALE = {0.6f, 0.6f};
static const sf::Vector2f PLATFORM_SIZE = {60.f, 17.f};
static const sf::Vector2f PLATFORM_SCALE = {0.75f, 0.75f};
static const sf::Vector2f PLAY_BUTTON_SIZE = {222.f, 80.f};
static const sf::Vector2f RESTART_BUTTON_SIZE = {224.f, 82.f};
static const sf::Vector2f CANCEL_BUTTON_SIZE = {224.f, 82.f};

struct BinaryData
{
    unsigned length;
    const unsigned char *data;
};

struct Assets
{
    Assets() = delete;

    static BinaryData ICON;
    static BinaryData FONT;
    static BinaryData BACKGROUND;
    static BinaryData DOODLER;
    static BinaryData PLATFORM;
    static BinaryData PLAY_BUTTON;
    static BinaryData RESTART_BUTTON;
    static BinaryData CANCEL_BUTTON;
};


#endif //DOODLE_JUMP_ASSETS_H
