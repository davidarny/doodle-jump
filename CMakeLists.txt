cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif ()

project(doodle-jump)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(NO_CONSOLE "")

if (WIN32 AND CMAKE_BUILD_TYPE MATCHES Release)
    set(NO_CONSOLE WIN32)
endif ()

add_executable(doodle-jump ${NO_CONSOLE}
    resources
    lib/incbin/incbin.h
    src/main.cpp
    src/consts.h
    src/EventLoop.cpp
    src/EventLoop.h
    src/Doodler.cpp
    src/Doodler.h
    src/IEntity.h
    src/Platform.cpp
    src/Platform.h
    src/IPhysicsObject.h
    src/Engine.cpp
    src/Engine.h
    src/KeyboardState.cpp
    src/KeyboardState.h
    src/View.cpp
    src/View.h
    src/GameState.cpp
    src/GameState.h
    src/IState.h
    src/enums.h
    src/States.cpp
    src/States.h
    src/Menu.cpp
    src/Menu.h
    src/Overlay.cpp
    src/Overlay.h
    src/Assets.cpp
    src/Assets.h
    src/Sprite.cpp
    src/Sprite.h)

target_compile_features(doodle-jump PUBLIC cxx_std_17)

if (EXISTS ${CMAKE_SOURCE_DIR}/cmake_modules)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
endif ()

if (EXISTS ${CMAKE_SOURCE_DIR}/lib/SFML/)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/lib/SFML/")
endif ()

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (${SFML_FOUND})
    include_directories(${SFML_INCLUDE_DIR})
    target_include_directories(doodle-jump PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(doodle-jump ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_compile_definitions(doodle-jump PRIVATE SFML_STATIC)
endif ()

if (${ZLIB_FOUND})
    target_include_directories(doodle-jump PRIVATE ${ZLIB_INCLUDE_DIRS})
    target_link_libraries(doodle-jump ${ZLIB_LIBRARIES})
endif ()

if (${BZIP2_FOUND})
    target_include_directories(doodle-jump PRIVATE ${BZIP2_INCLUDE_DIR})
    target_link_libraries(doodle-jump ${BZIP2_LIBRARIES})
endif ()
