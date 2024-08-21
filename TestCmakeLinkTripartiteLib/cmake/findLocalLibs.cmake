# Find Libs Name
set(BUTTON)

set(DIR ${CMAKE_SOURCE_DIR}/out/install/x64-${CMAKE_BUILD_TYPE}/${CMAKE_BUILD_TYPE})
set(INCLUDE_DIRS ${DIR}/include)
set(LIB_DIRS ${DIR}/lib)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    find_library(BUTTON libButton REQUIRED PATHS ${LIB_DIRS})
else()
    find_library(BUTTON libButton REQUIRED PATHS ${LIB_DIRS})
endif()
#copy dll to executable dir
if(MSVC)
    file(GLOB dlls_to_copy "${LIB_DIRS}/*.dll")
    file(GLOB pdbs_to_copy "${LIB_DIRS}/*.pdb")
    file(COPY ${dlls_to_copy} ${pdbs_to_copy} DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
endif()