#include "traits.hpp"

#include <gtest/gtest.h>

#include <deque>
#include <forward_list>
#include <string>

using namespace traits;

namespace
{

struct CustomType final
{
};

TEST(TraitsTest, ShouldReturnTrueWhenVectorPassedToIsVector)
{
    EXPECT_TRUE(is_vector_v<std::vector<int>>);
    EXPECT_TRUE(is_vector_v<std::vector<CustomType>>);
}

TEST(TraitsTest, ShouldReturnFalseWhenNonVectorPassedToIsVector)
{
    EXPECT_FALSE(is_vector_v<std::list<int>>);
    EXPECT_FALSE(is_vector_v<std::deque<std::string>>);
    EXPECT_FALSE(is_vector_v<CustomType>);
}

TEST(TraitsTest, ShouldReturnTrueWhenListPassedToIsList)
{
    EXPECT_TRUE(is_list_v<std::list<int>>);
    EXPECT_TRUE(is_list_v<std::list<std::vector<int>>>);
}

TEST(TraitsTest, ShouldReturnFalseWhenNonListPassedToIsList)
{
    EXPECT_FALSE((is_list_v<std::map<int, int>>));
    EXPECT_FALSE(is_list_v<std::forward_list<int>>);
}

TEST(TraitsTest, ShouldReturnTrueWhenAllTypesAreSame)
{
    EXPECT_TRUE((all_types_are_same<int, int, int>));
    EXPECT_TRUE((all_types_are_same<std::string, std::string>));
    EXPECT_TRUE((all_types_are_same<CustomType, CustomType>));
}

TEST(TraitsTest, ShouldReturnFalseWhenTypesAreDifferent)
{
    EXPECT_FALSE((all_types_are_same<int, double, int>));
    EXPECT_FALSE((all_types_are_same<char, std::string>));
    EXPECT_FALSE((all_types_are_same<std::vector<int>, std::list<int>>));
}

TEST(TraitsTest, ShouldReturnTrueWhenSingleTypePassedToAllTypesSame)
{
    EXPECT_TRUE(all_types_are_same<int>);
}

}  // namespace