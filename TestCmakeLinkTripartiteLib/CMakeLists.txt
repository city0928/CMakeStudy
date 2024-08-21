cmake_minimum_required(VERSION 3.16)
project(TestCmakeLinkTripartiteLib LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include(cmake/qt.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)

qt_standard_project_setup()

set(PROJECT_SOURCES
    src/
    src/main.cpp
    src/TestCmakeLinkTripartiteLib.ui
    src/TestCmakeLinkTripartiteLib.h
    src/TestCmakeLinkTripartiteLib.cpp
)

#qt_add_executable(TestCmakeLinkTripartiteLib ${PROJECT_SOURCES})
add_executable(TestCmakeLinkTripartiteLib ${PROJECT_SOURCES})

include(./cmake/findLocalLibs.cmake)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${INCLUDE_DIRS}
)

target_link_libraries(TestCmakeLinkTripartiteLib
    PUBLIC
        ${BUTTON}
        ${QtLibs}
)