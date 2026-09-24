cmake_minimum_required(VERSION 3.20)
project(my_learning_project C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)
# add_compile_options(-g)
# add_compile_options("-isystem" "/usr/lib/gcc/x86_64-linux-gnu/11/include")

# file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB SUB_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "[0-9]*")

# 2. 遍历扫描到的目录
foreach(DIR ${SUB_DIRS})
    # 确保它是一个文件夹，并且里面包含 CMakeLists.txt，防止误导入普通文件
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DIR} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/CMakeLists.txt)
        # message(STATUS "自动发现并导入大章节目录: ${DIR}")
        add_subdirectory(${DIR})
    endif()
endforeach()