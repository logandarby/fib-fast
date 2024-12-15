include(FetchContent)

# Set up Google Test

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

include(GoogleTest)


# Add Tests

add_executable(tests tests.cpp)
# gtest_discover_tests(tests)
target_include_directories(tests PRIVATE "../src")
target_link_libraries(tests PRIVATE GTest::GTest FibFast_Lib)

add_test(tests_gtest tests)
