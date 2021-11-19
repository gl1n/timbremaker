cmake_minimum_required(VERSION 3.16)
project(TimbreMaker)

set(CMAKE_CXX_STANDARD 11)
# 设置可调试
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 添加头文件目录
# include_directories(${CMAKE_SOURCE_DIR}/include) //与下面那行等价
include_directories(include)
# 添加源文件目录
add_subdirectory(src)
# 指定生成目标
add_executable(main main.cpp)
# 链接静态库
target_link_libraries(main timbre_maker)