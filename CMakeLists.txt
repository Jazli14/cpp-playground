cmake_minimum_required(VERSION 3.20)

project(cppPlayground)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
	add_compile_options(/Zc:__cplusplus)
endif()

add_executable(unique_ptr unique_ptr.cpp)
add_executable(shared_ptr shared_ptr.cpp)

target_compile_options(unique_ptr PRIVATE /W4)
target_compile_options(shared_ptr PRIVATE /W4)
