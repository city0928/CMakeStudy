# 安装头文件
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/out/install")

# install all .h files
install(FILES ${BUTTON_HEAD_FILES}
    DESTINATION ${CMAKE_BUILD_TYPE}/include/Button
)
# install pdb
install(
    FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> 
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
    DESTINATION ${CMAKE_BUILD_TYPE}/lib
)
#install .dll and .lib
install(TARGETS ${PROJECT_NAME}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
    RUNTIME DESTINATION ${CMAKE_BUILD_TYPE}/bin
    RUNTIME DESTINATION ${CMAKE_BUILD_TYPE}/lib
    LIBRARY DESTINATION ${CMAKE_BUILD_TYPE}/lib
    ARCHIVE DESTINATION ${CMAKE_BUILD_TYPE}/lib
)