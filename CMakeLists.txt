cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(FibFast)

# Sources
# MY_SOURCES is defined to be a list of all the source files in src that aren't main.cpp
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM MY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_executable("${CMAKE_PROJECT_NAME}")
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

# Set DEBUG flags
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _DEBUG)
endif()

# Add Tests

enable_testing()
add_subdirectory(tests)

# Final Link
add_library("${CMAKE_PROJECT_NAME}_Lib" STATIC ${MY_SOURCES})
# target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" "${MY_SOURCES}")
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_PROJECT_NAME}_Lib")
target_include_directories("${CMAKE_PROJECT_NAME}_Lib" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
