cmake_minimum_required(VERSION 3.16)
project(CombatMaster LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/mingw_64")   # <-- new line

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(CombatMaster
    main.cpp
    core/src/Combatant.cpp
    core/src/Enemy.cpp
    core/src/PlayerCharacter.cpp
    ui/mainwindow.cpp
)

target_include_directories(CombatMaster PRIVATE core/include)
target_link_libraries(CombatMaster PRIVATE Qt6::Widgets)

add_executable(QtSmokeTest qt_smoke_test.cpp)
target_link_libraries(QtSmokeTest PRIVATE Qt6::Widgets)