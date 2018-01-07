#include "Assets.h"

INCBIN(ICON_BIN, "../resources/icon.png");
INCBIN(FONT_BIN, "../resources/opensans.ttf");
INCBIN(BACKGROUND_BIN, "../resources/background.png");
INCBIN(DOODLER_BIN, "../resources/doodler.png");
INCBIN(PLATFORM_BIN, "../resources/platform.png");
INCBIN(PLAY_BUTTON_BIN, "../resources/play-button.png");
INCBIN(RESTART_BUTTON_BIN, "../resources/play-again-button.png");
INCBIN(CANCEL_BUTTON_BIN, "../resources/cancel-button.png");

BinaryData Assets::ICON = BinaryData{ICON_BIN_size, ICON_BIN_data};

BinaryData Assets::FONT = BinaryData{FONT_BIN_size, FONT_BIN_data};

BinaryData Assets::BACKGROUND = BinaryData{BACKGROUND_BIN_size, BACKGROUND_BIN_data};

BinaryData Assets::DOODLER = BinaryData{DOODLER_BIN_size, DOODLER_BIN_data};

BinaryData Assets::PLATFORM = BinaryData{PLATFORM_BIN_size, PLATFORM_BIN_data};

BinaryData Assets::PLAY_BUTTON = BinaryData{PLAY_BUTTON_BIN_size, PLAY_BUTTON_BIN_data};

BinaryData Assets::RESTART_BUTTON = BinaryData{RESTART_BUTTON_BIN_size, RESTART_BUTTON_BIN_data};

BinaryData Assets::CANCEL_BUTTON = BinaryData{CANCEL_BUTTON_BIN_size, CANCEL_BUTTON_BIN_data};
