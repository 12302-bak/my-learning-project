
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB MAINC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")
get_filename_component(TARGET_NAME  ${MAINC} NAME_WE)

# add_library(calc SHARED ${SRC_LIST})
add_executable(${TARGET_NAME} ${MAINC} ${SRC_LIST})