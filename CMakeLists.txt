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
    FourByFour_Board.cpp
    FourByFour_UI.cpp
    FiveByFiveTTT_Classes.cpp
    PyramidTTT_Classes.cpp
    WordTTT_Classes.cpp
    UltimateTTT_Classes.cpp
)
configure_file(${CMAKE_SOURCE_DIR}/dic.txt ${CMAKE_BINARY_DIR}/Debug/dic.txt COPYONLY)
target_include_directories(MiniBoards PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})