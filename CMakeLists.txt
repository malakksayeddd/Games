cmake_minimum_required(VERSION 3.10)
project(MiniBoards)


add_executable(MiniBoards 
    main.cpp 
    MenuManager.cpp
    XO_Classes.cpp
    NumericalTTT_Classes.cpp
    SUS_Classes.cpp
    FourInARow_Classes.cpp
    InfinityTTT_Classes.cpp
    MisereTTT_Classes.cpp
    ObstaclesTTT_Classes.cpp
)

target_include_directories(MiniBoards PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})