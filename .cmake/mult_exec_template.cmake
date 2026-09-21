
file(GLOB ALL_C_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c")

# 2. 循环处理每一个文件
foreach(FILE_PATH ${ALL_C_FILES})

    # NAME_WE (Name Without Extension), NAME, EXT, ABSOLUTE
    get_filename_component(TARGET_NAME ${FILE_PATH} NAME_WE)
    
    # 过滤掉不需要独立编译的文件（比如公共函数库 utils.c，如果没有则删掉这几行）
    if(NOT "${TARGET_NAME}" STREQUAL "utils") 
        # 自动注册可执行文件
        add_executable(${TARGET_NAME} ${FILE_PATH})
        
        # 如果需要链接公共的 utils.c，可以在这里统一链接
        # target_sources(${TARGET_NAME} PRIVATE utils.c)
    endif()
endforeach()


file(GLOB SUB_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
foreach(DIR ${SUB_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DIR} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/CMakeLists.txt)
        # message(STATUS "自动发现并导入大章节目录: ${DIR}")
        add_subdirectory(${DIR})
    endif()
endforeach()