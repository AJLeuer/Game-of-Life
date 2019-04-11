cmake_minimum_required(VERSION 3.6.2)
project(Game_of_Life)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake Modules" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS audio graphics window system)

include_directories(Source)
include_directories(Source/Model)
include_directories(Source/Util)
include_directories(Source/View)
include_directories(/usr/local/include)
include_directories(${SFML_INCLUDE_DIR})

add_executable(Game_of_Life
        Source/Model/Cell.cpp
        Source/Model/Cell.hpp
        Source/Model/Grid.cpp
        Source/Model/Grid.hpp
        Source/Util/Config.cpp
        Source/Util/Random.hpp
        Source/Util/Util.cpp
        Source/Util/Util.hpp
        Source/Util/Vect.hpp
        Source/View/DisplayData.cpp
        Source/View/DisplayData.hpp
        Source/View/Window.cpp
        Source/Game.cpp
        Source/Game.hpp
        Source/main.cpp)

add_library(SFML SHARED IMPORTED)

#target_link_libraries(Game_of_Life ${SFML_STATIC_LIBRARIES})
target_link_libraries(Game_of_Life ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})