cmake_minimum_required(VERSION 3.16)

include_directories(../include)
# 将当前目录的源文件放入变量source_list中
aux_source_directory(. source_list)

add_library(timbre_maker ${source_list})