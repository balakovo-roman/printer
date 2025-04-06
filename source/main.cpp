#include <cstdint>

#include "printer/printer.hpp"

using namespace std::string_literals;

int main()
{
    printer::Printer printer{std::cout};

    printer.Print(int8_t{-1});
    printer.Print(uint16_t{0});
    printer.Print(int32_t{2130706433});
    printer.Print(int64_t{8875824491850138409});
    printer.Print("Hello, World!"s);
    printer.Print(std::vector{100, 200, 300, 400});
    printer.Print(std::list<short>{400, 300, 200, 100});
    printer.Print(std::make_tuple(123, 456, 789, 0));
}