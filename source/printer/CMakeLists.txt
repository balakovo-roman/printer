cmake_minimum_required(VERSION 3.28)

make_interface_lib(printer printer.hpp)

target_link_libraries(printer INTERFACE traits)

set(TEST_SOURCES printer_test.cpp)

make_main_test(printer "${TEST_SOURCES}" "printer")