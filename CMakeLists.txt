# cmake project
cmake_minimum_required(VERSION 3.10)

Project(vizSTLPerf)

MESSAGE(STATUS "project name is $(PROJECT_NAME)")

INCLUDE_DIRECTORIES(include)
# AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# 设置CMAKE的C++的标准版本，这里以C++14为标准
set(CMAKE_CXX_STANDARD 14)
# 设置各个目录的绝对路径，以便后续使用
set(TOP_DIR ${PROJECT_SOURCE_DIR})
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# 设置源文件
set(SRC_LIST
    ${SRC_DIR}/ListPerf.cc
    ${SRC_DIR}/VectorPerf.cc
    ${SRC_DIR}/main.cc)

MESSAGE(STATUS "project_source_dir = " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "include dir = " ${INCLUDE_DIR})
MESSAGE(STATUS "top dir = " ${TOP_DIR})
MESSAGE(STATUS "source dir = " ${SRC_DIR})
MESSAGE(STATUS "source list = " ${SRC_LIST})

add_executable(vizSTLPerf ${SRC_LIST})
# 设置依赖库
TARGET_LINK_LIBRARIES(vizSTLPerf
    -lpthread
)
