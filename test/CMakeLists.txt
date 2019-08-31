FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.8.0
)


FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.9.1
)

FetchContent_MakeAvailable(catch2)
FetchContent_MakeAvailable(googletest)

add_executable(test_lib system_data_types_test.cpp)
target_link_libraries(test_lib PUBLIC systems_lib gtest gtest_main Catch2::Catch2)
#target_compile_options(test_lib  INTERFACE -std=c++17 -O3)