include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    componentes-test 
    componentes_test.cpp
)

target_link_libraries(
  componentes-test
  gtest_main
)

add_executable(
    cabine-test
    cabine_test.cpp
    ../src/cabine.cpp
)

target_link_libraries(
  cabine-test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(
    componentes-test 
    cabine-test
)