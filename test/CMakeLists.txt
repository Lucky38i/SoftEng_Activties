# see https://cmake.org/cmake/help/latest/module/FindBoost.html
# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set(Boost_USE_STATIC_LIBSS OFF)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})

add_executable(test test.cpp)

# Note: a target should be already defined using 'add_executable' or 'add_library' 
target_link_libraries(test ${Boost_LIBRARIES})