cmake_minimum_required(VERSION 2.6)
project(zhangsjson_test C)

add_library(zhangsjson zhangsjson.c)
add_executable(zhangsjson_test test.c)
target_link_libraries(zhangsjson_test zhangsjson)
