cmake_minimum_required(VERSION 3.6.2)
project(Game_of_Life)

set(CMAKE_CXX_STANDARD 14)

include_directories(Source)
include_directories(Source/Model)
include_directories(Source/Util)
include_directories(Source/View)

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
        #Source/View/DisplayData.mm
        Source/View/Window.cpp
        Source/View/Window.mm
        Source/Game.cpp
        Source/Game.hpp
        Source/main.cpp)
