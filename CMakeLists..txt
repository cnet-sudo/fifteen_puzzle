cmake_minimum_required(VERSION 3.10)
project(FifteenPuzzle)

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к SFML (если не установлена в системе)
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML" CACHE PATH "Path to SFML")

# Ищем SFML 2.6.1
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Указываем все исходные файлы
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

# Создаём исполняемый файл
add_executable(FifteenPuzzle ${SOURCES})

# Добавляем файл ресурсов для Windows
target_sources(FifteenPuzzle PRIVATE fifteen_puzzle.rc)

# Линкуем SFML
target_link_libraries(FifteenPuzzle sfml-graphics sfml-window sfml-system)

# Копируем DLL файлы SFML в директорию сборки (для Windows)
if(WIN32)
    add_custom_command(TARGET FifteenPuzzle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/SFML-2.6.1/bin"
        $<TARGET_FILE_DIR:FifteenPuzzle>)
endif()

# Копируем ресурсы (если есть папка assets/)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})