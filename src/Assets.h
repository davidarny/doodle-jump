#ifndef DOODLE_JUMP_ASSETS_H
#define DOODLE_JUMP_ASSETS_H
#define INCBIN_PREFIX
#define INCBIN_STYLE INCBIN_STYLE_SNAKE

#include <SFML/Graphics.hpp>
#include "../lib/incbin/incbin.h"

static const sf::Vector2u ICON_IMAGE_SIZE = {32, 32};
static const sf::Vector2f BACKGROUND_SPRITE_SIZE = {600.f, 800.f};
static const sf::Vector2f DOODLER_SPRITE_SIZE = {50.f, 45.f};
static const sf::Vector2f PLATFORM_SPRITE_SIZE = {40.f, 12.5f};
static const sf::Vector2f BUTTON_SPRITE_SIZE = {220.f, 80.f};

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
