#pragma once

#include <climits>
#include <iostream>
#include <string_view>

#include "../traits/traits.hpp"

namespace printer
{
class Printer final
{
   public:
    explicit Printer(std::ostream& os = std::cout) : os_(os) {}

    template <typename T>
    std::enable_if_t<std::is_integral_v<T>, void> Print(T value)
    {
        for (std::size_t i = sizeof(T); i > 0; --i)
        {
            const auto byte =
                static_cast<std::byte>((value >> ((i - 1) * CHAR_BIT)) & 0xFF);
            os_ << std::to_integer<unsigned>(byte);
            if (i != 1)
                os_ << '.';
        }
        os_ << '\n';
    }

    template <typename T>
    std::enable_if_t<std::is_convertible_v<T, std::string_view>, void> Print(
        const T& string)
    {
        os_ << string << '\n';
    }

    template <typename T>
    std::enable_if_t<
        std::disjunction_v<traits::is_vector<T>, traits::is_list<T>>, void>
    Print(const T& container)
    {
        const auto end = std::cend(container);
        const auto prev = std::prev(end);
        for (auto it = std::cbegin(container); it != end; ++it)
        {
            os_ << *it;
            if (it != prev)
                os_ << '.';
        }
        os_ << '\n';
    }

    template <typename... Args>
    void Print(const std::tuple<Args...>& tuple)
    {
        static_assert(traits::all_types_are_same<Args...>,
                      "All tuple elements must be of the same type");

        std::apply(
            [this](const Args&... args)
            {
                std::size_t n{0};
                ((os_ << args
                      << (++n != sizeof...(Args) ? std::string(1, '.')
                                                 : std::string{})),
                 ...);
                os_ << '\n';
            },
            tuple);
    }

   private:
    std::ostream& os_;
};

}  // namespace printer