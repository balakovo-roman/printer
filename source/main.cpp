
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>

template <typename T>
std::enable_if_t<std::is_integral_v<T>, void> print_ip(T value)
{
    for (std::size_t i = sizeof(T); i > 0; --i)
    {
        const auto byte =
            static_cast<std::byte>((value >> ((i - 1) * CHAR_BIT)) & 0xFF);

        std::cout << std::to_integer<unsigned>(byte);

        if (i != 1)
        {
            std::cout << '.';
        }
    }

    std::cout << '\n';
}

int main()
{
    print_ip(int8_t{-1});
    print_ip(uint16_t{0});
    print_ip(int32_t{2130706433});
}