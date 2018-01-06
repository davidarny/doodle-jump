#ifndef DOODLE_JUMP_ASSETS_H
#define DOODLE_JUMP_ASSETS_H

#define INCBIN_PREFIX

#define INCBIN_STYLE INCBIN_STYLE_SNAKE

#include "../lib/incbin/incbin.h"

struct BinaryData
{
    unsigned size;
    const unsigned char *data;
};

struct Assets
{
    Assets() = delete;

    static BinaryData ICON;

    static BinaryData FONT;
};


#endif //DOODLE_JUMP_ASSETS_H
