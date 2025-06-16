# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(native_multilib)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)


add_library(entry SHARED napi_init.cpp)
add_library(leak SHARED napi_init_leak.cpp)
add_library(dynamic SHARED napi_init_dynamic.cpp)

target_link_libraries(entry PUBLIC libace_napi.z.so)
target_link_libraries(leak PUBLIC libace_napi.z.so libhilog_ndk.z.so)
target_link_libraries(dynamic PUBLIC libace_napi.z.so libhilog_ndk.z.so)