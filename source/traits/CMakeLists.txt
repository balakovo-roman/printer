cmake_minimum_required(VERSION 3.28)

make_interface_lib(traits traits.hpp)

set(TEST_SOURCES traits_test.cpp)

make_main_test(traits "${TEST_SOURCES}" "traits")