cmake_minimum_required(VERSION 3.25)
project(CustomButton LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

# ²éÕÒ Qt °ü
include(qtcomp.cmake)

option(UseSub ON)
option(UseSubTester OFF)
option(UseTestCmakeLinkTripartiteLib OFF)

if(UseSub)
    add_subdirectory(Button)
endif()

if(UseSubTester)
    add_subdirectory(LibTester)
endif()

if(UseTestCmakeLinkTripartiteLib)
    add_subdirectory(TestCmakeLinkTripartiteLib)
endif()