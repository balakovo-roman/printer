#include "printer.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <string_view>

namespace
{

using namespace std::string_literals;
using namespace std::string_view_literals;

class PrinterTest : public ::testing::Test
{
   protected:
    void SetUp() override { printer = std::make_unique<printer::Printer>(ss); }

    std::string GetOutput() const { return ss.str(); }

    std::stringstream ss;
    std::unique_ptr<printer::Printer> printer;
};

TEST_F(PrinterTest, ShouldPrintIntegralValueCorrectlyWhenInt8Passed)
{
    // Act
    printer->Print(int8_t{-1});

    // Assert
    EXPECT_EQ(GetOutput(), "255\n");
}

TEST_F(PrinterTest, ShouldPrintIntegralValueCorrectlyWhenInt16Passed)
{
    // Act
    printer->Print(int16_t{0});

    // Assert
    EXPECT_EQ(GetOutput(), "0.0\n");
}

TEST_F(PrinterTest, ShouldPrintIntegralValueCorrectlyWhenInt32Passed)
{
    // Act
    printer->Print(int32_t{2130706433});

    // Assert
    EXPECT_EQ(GetOutput(), "127.0.0.1\n");
}

TEST_F(PrinterTest, ShouldPrintStringCorrectlyWhenStringLiteralPassed)
{
    // Act
    printer->Print("Hello, World!");

    // Assert
    EXPECT_EQ(GetOutput(), "Hello, World!\n");
}

TEST_F(PrinterTest, ShouldPrintStringCorrectlyWhenStdStringPassed)
{
    // Act
    printer->Print("Hello, World!"s);

    // Assert
    EXPECT_EQ(GetOutput(), "Hello, World!\n");
}

TEST_F(PrinterTest, ShouldPrintStringCorrectlyWhenStdStringViewPassed)
{
    // Act
    printer->Print("Hello, World!"sv);

    // Assert
    EXPECT_EQ(GetOutput(), "Hello, World!\n");
}

TEST_F(PrinterTest, ShouldPrintContainerElementsCorrectlyWhenVectorPassed)
{
    // Act
    printer->Print(std::vector{100, 200, 300, 400});

    // Assert
    EXPECT_EQ(GetOutput(), "100.200.300.400\n");
}

TEST_F(PrinterTest, ShouldPrintContainerElementsCorrectlyWhenListPassed)
{
    // Act
    printer->Print(std::list<short>{400, 300, 200, 100});

    // Assert
    EXPECT_EQ(GetOutput(), "400.300.200.100\n");
}

TEST_F(PrinterTest, ShouldPrintTupleElementsCorrectlyWhenHomogeneousTuplePassed)
{
    // Act
    printer->Print(std::make_tuple(123, 456, 789, 0));

    // Assert
    EXPECT_EQ(GetOutput(), "123.456.789.0\n");
}

}  // namespace