#pragma once

#include <list>
#include <vector>

namespace traits
{

template <template <typename...> class Container, typename... Ts>
struct is_container : std::false_type
{
};

template <template <typename...> class Container, typename... Ts>
struct is_container<Container, Container<Ts...>> : std::true_type
{
};

template <typename... Ts>
using is_vector = is_container<std::vector, Ts...>;

template <typename... Ts>
constexpr bool is_vector_v = is_vector<Ts...>::value;

template <typename... Ts>
using is_list = is_container<std::list, Ts...>;

template <typename... Ts>
constexpr bool is_list_v = is_list<Ts...>::value;

template <typename T, typename... Ts>
constexpr bool all_types_are_same = std::conjunction_v<std::is_same<T, Ts>...>;

}  // namespace traits