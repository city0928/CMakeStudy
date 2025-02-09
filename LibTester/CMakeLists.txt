cmake_minimum_required(VERSION 3.16)
project(LibTester LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include(../qt.cmake)

set(CMAKE_CXX_STANDARD 17)
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
    src/QtWidgetClass.ui
    src/QtWidgetClass.h
    src/QtWidgetClass.cpp
)

#qt_add_executable(Tester ${TESTER_SOURCES})
add_executable(LibTester ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

set(DIR ${CMAKE_CURRENT_LIST_DIR}/../out/install/x64-${CMAKE_BUILD_TYPE}/Button/${CMAKE_BUILD_TYPE})
set(INCLUDE_DIRS ${DIR}/include)
set(LIB_DIRS ${DIR}/lib)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    find_library(BUTTON Button REQUIRED PATHS ${LIB_DIRS})
else()
    find_library(BUTTON Button REQUIRED PATHS ${LIB_DIRS})
endif()
if(MSVC)
    file(GLOB dlls_to_copy "${LIB_DIRS}/*.dll")
    file(GLOB pdbs_to_copy "${LIB_DIRS}/*.pdb")
    file(COPY ${dlls_to_copy} ${pdbs_to_copy} DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
endif()
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${INCLUDE_DIRS}
)

target_link_libraries(LibTester
    PUBLIC
        ${Button}
        ${LinkLibsQt}
)