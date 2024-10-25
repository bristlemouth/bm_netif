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

function(create_gtest src_name more_sources)
    set(test_name ${src_name}_test)
    add_executable(${test_name} src/${test_name}.cpp ${more_sources})
    target_link_libraries(${test_name} GTest::gtest_main)
    target_link_libraries(${test_name} bmnetif)
    gtest_discover_tests(${test_name})
endfunction()

set(bm_adin2111_sources ${bm_common_SOURCE_DIR}/src/aligned_malloc.c)
create_gtest(bm_adin2111 "${bm_adin2111_sources}")
