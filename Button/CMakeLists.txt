cmake_minimum_required(VERSION 3.25)
project(Button LANGUAGES CXX)

include(../cmake/src.cmake)# source code.

include(../cmake/productinfo.cmake)# product detail info.

add_library(Button SHARED ${PUBLIC_FILES} ${MY_VERSIONINFO_RC})

include(../cmake/install.cmake)# this project install dirs

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

# 当前动态库应用于其他头文件
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${BUTTON_HEAD_FILES}")
# 编译语言信息
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
# 动、静态库名称 生成 添加前缀
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "lib" IMPORT_PREFIX "lib") 

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${QtLibs}
)

# 定义导出宏
target_compile_definitions(Button
    PRIVATE
    CUSTOMBUTTON_LIB
)
