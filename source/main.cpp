
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <string_view>
#include <type_traits>
#include <vector>

using namespace std::string_literals;
using namespace std::string_view_literals;

template <template <typename...> class Container, typename T>
struct is_container : std::false_type
{
};

template <template <typename...> class Container, typename... Types>
struct is_container<Container, Container<Types...>> : std::true_type
{
};

template <typename T>
using is_vector = is_container<std::vector, T>;

template <typename T>
using is_list = is_container<std::list, T>;

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

template <typename T>
std::enable_if_t<std::is_convertible_v<T, std::string_view>, void> print_ip(
    const T& string)
{
    std::cout << string << '\n';
}

template <typename T>
std::enable_if_t<std::disjunction_v<is_vector<T>, is_list<T>>, void> print_ip(
    const T& container)
{
    const auto end = std::cend(container);
    const auto prev = std::prev(end);

    for (auto it = std::cbegin(container); it != end; ++it)
    {
        std::cout << *it;

        if (it != prev)
        {
            std::cout << '.';
        }
    }

    std::cout << '\n';
}

template <typename T, typename... Ts>
constexpr bool all_types_are_same = std::conjunction_v<std::is_same<T, Ts>...>;

template <typename... Args>
void print_ip(const std::tuple<Args...>& tuple)
{
    static_assert(all_types_are_same<Args...>,
                  "All tuple elements must be of the same type");

    std::apply(
        [](const Args&... args)
        {
            std::size_t n{0};
            ((std::cout << args << (++n != sizeof...(Args) ? '.' : char{})),
             ...);
            std::cout << '\n';
        },
        tuple);
}

int main()
{
    print_ip(int8_t{-1});
    print_ip(uint16_t{0});
    print_ip(int32_t{2130706433});
    print_ip(int64_t{8875824491850138409});
    print_ip("Hello, World!"s);
    print_ip(std::vector{100, 200, 300, 400});
    print_ip(std::list<short>{400, 300, 200, 100});
    print_ip(std::make_tuple(123, 456, 789, 0));
}