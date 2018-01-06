#include "Assets.h"

INCBIN(ICON_BIN, "../resources/icon.png");
INCBIN(FONT_BIN, "../resources/opensans.ttf");

BinaryData Assets::ICON = BinaryData{ICON_BIN_size, ICON_BIN_data};

BinaryData Assets::FONT = BinaryData{FONT_BIN_size, FONT_BIN_data};
