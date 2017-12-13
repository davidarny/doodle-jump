cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(doodle_jump)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

if (WIN32 AND CMAKE_BUILD_TYPE MATCHES Release)
    add_executable(doodle_jump WIN32 main.cpp resources consts.h EventLoop.cpp EventLoop.h Doodler.cpp Doodler.h Entity.h Platform.cpp Platform.h)
else ()
    add_executable(doodle_jump main.cpp resources consts.h EventLoop.cpp EventLoop.h Doodler.cpp Doodler.h Entity.h Platform.cpp Platform.h)
endif ()

target_compile_features(doodle_jump PUBLIC cxx_std_17)

if (EXISTS ${CMAKE_SOURCE_DIR}/cmake_modules)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
endif ()

if (EXISTS ${CMAKE_SOURCE_DIR}/lib/sfml/)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/lib/sfml/")
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
    target_include_directories(doodle_jump PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(doodle_jump ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_compile_definitions(doodle_jump PRIVATE SFML_STATIC)
endif ()

if (${ZLIB_FOUND})
    target_include_directories(doodle_jump PRIVATE ${ZLIB_INCLUDE_DIRS})
    target_link_libraries(doodle_jump ${ZLIB_LIBRARIES})
endif ()

if (${BZIP2_FOUND})
    target_include_directories(doodle_jump PRIVATE ${BZIP2_INCLUDE_DIR})
    target_link_libraries(doodle_jump ${BZIP2_LIBRARIES})
endif ()

file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
