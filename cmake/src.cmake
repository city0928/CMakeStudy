set(INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/../Button/src
)

set(BUTTON_HEAD_FILES
    ${CMAKE_CURRENT_LIST_DIR}/../Button/src/custombutton_global.h
    ${CMAKE_CURRENT_LIST_DIR}/../Button/src/CustomButton.h
)
set(BUTTON_CPP_FILES
    ${CMAKE_CURRENT_LIST_DIR}/../Button/src/CustomButton.cpp
)

set(PUBLIC_FILES
    ${BUTTON_HEAD_FILES}
    ${BUTTON_CPP_FILES}
)
