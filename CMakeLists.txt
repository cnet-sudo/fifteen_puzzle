cmake_minimum_required(VERSION 3.10)
project(FifteenPuzzle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

set(SOURCES
    Button.cpp
    ColorfulText.cpp
    fifteen_puzzle.cpp
    FifteenPuzzle.cpp
    GameScreen.cpp
    MainMenu.cpp
    ResourceManager.cpp
    RulesScreen.cpp
    Screen.cpp
    Transition.cpp
)

add_executable(FifteenPuzzle ${SOURCES})

target_sources(FifteenPuzzle PRIVATE fifteen_puzzle.rc)

target_link_libraries(FifteenPuzzle sfml-graphics sfml-window sfml-system)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})