#include "Assets.h"

INCBIN(ICON_BIN, "../resources/icon.png");
INCBIN(FONT_BIN, "../resources/al-seana.ttf");
INCBIN(BACKGROUND_BIN, "../resources/background.png");
INCBIN(DOODLER_BIN, "../resources/doodler.png");
INCBIN(PLATFORM_BIN, "../resources/platform.png");
INCBIN(PLATFORM_SPRING_BIN, "../resources/platform-spring.png");
INCBIN(PLATFORM_TRAMPOLINE_BIN, "../resources/platform-trampoline.png");
INCBIN(PLAY_BUTTON_BIN, "../resources/play-button.png");
INCBIN(RESTART_BUTTON_BIN, "../resources/play-again-button.png");
INCBIN(CANCEL_BUTTON_BIN, "../resources/cancel-button.png");

BinaryData Assets::ICON = BinaryData{static_cast<size_t>(ICON_BIN_size), ICON_BIN_data};

BinaryData Assets::FONT = BinaryData{static_cast<size_t>(FONT_BIN_size), FONT_BIN_data};

BinaryData Assets::BACKGROUND = BinaryData{static_cast<size_t>(BACKGROUND_BIN_size), BACKGROUND_BIN_data};

BinaryData Assets::DOODLER = BinaryData{static_cast<size_t>(DOODLER_BIN_size), DOODLER_BIN_data};

BinaryData Assets::PLATFORM = BinaryData{static_cast<size_t>(PLATFORM_BIN_size), PLATFORM_BIN_data};

BinaryData Assets::PLATFORM_SPRING = BinaryData{static_cast<size_t>(PLATFORM_SPRING_BIN_size),
                                                PLATFORM_SPRING_BIN_data};

BinaryData Assets::PLAY_BUTTON = BinaryData{static_cast<size_t>(PLAY_BUTTON_BIN_size), PLAY_BUTTON_BIN_data};

BinaryData Assets::RESTART_BUTTON = BinaryData{static_cast<size_t>(RESTART_BUTTON_BIN_size), RESTART_BUTTON_BIN_data};

BinaryData Assets::CANCEL_BUTTON = BinaryData{static_cast<size_t>(CANCEL_BUTTON_BIN_size), CANCEL_BUTTON_BIN_data};

BinaryData Assets::PLATFORM_TRAMPOLINE = BinaryData{static_cast<size_t>(PLATFORM_TRAMPOLINE_BIN_size),
                                                    PLATFORM_TRAMPOLINE_BIN_data};
