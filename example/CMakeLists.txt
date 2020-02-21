cmake_minimum_required (VERSION 3.10)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(UHookExample LANGUAGES CXX)
    find_package(UHook CONFIG REQUIRED)
    if (${UHook_FOUND})
        message(STATUS "Found UHook ${UHOOK_VERSION}")
        message(STATUS "Using UHookConfig.cmake in: ${UHook_DIR}")
        include_directories(${UHOOK_INCLUDE_DIRS})
    endif()
endif()

add_executable(main main.cpp)
add_library(DumpArgs SHARED DumpArgs.cpp)

target_link_libraries(main UHook ${CMAKE_DL_LIBS})
target_link_libraries(DumpArgs UHook)
