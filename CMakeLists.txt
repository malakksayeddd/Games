project(MiniBoards)


add_executable(MiniBoards main.cpp MenuManager.cpp XO_Classes.cpp)

target_include_directories(MiniBoards PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})