cmake_minimum_required(VERSION 3.29)

# googletest utilizes C++
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Building Unit Tests")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

FetchContent_Declare(
  fff
  GIT_REPOSITORY https://github.com/meekrosoft/fff.git
  GIT_TAG        5111c61
)
FetchContent_MakeAvailable(fff)

include_directories(${fff_SOURCE_DIR})

function(create_gtest src_name)
    set(test_name ${src_name}_test)
    set(test_src src/${test_name}.cpp)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} GTest::gtest_main)
    target_link_libraries(${test_name} bmnetif)
    gtest_discover_tests(${test_name})
endfunction()

create_gtest("bm_adin2111")
