cmake_minimum_required(VERSION 3.28)
project(MonkeyTyper LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/Word.cpp
        src/Word.h
        src/Health.cpp
        src/Health.h
        src/ScoreManager.cpp
        src/ScoreManager.h
        src/Scoreboard.cpp
        src/Scoreboard.h
        src/PlayBtn.cpp
        src/PlayBtn.h
        src/MenuBackBtn.cpp
        src/MenuBackBtn.h
        src/ScoreboardBtn.cpp
        src/ScoreboardBtn.h
        src/FontManager.cpp
        src/FontManager.h
        src/OptionsBtn.cpp
        src/OptionsBtn.h
        src/OptionsManager.cpp
        src/OptionsManager.h
        src/Difficulty.h
        src/DifficultyManager.cpp
        src/DifficultyManager.h
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
