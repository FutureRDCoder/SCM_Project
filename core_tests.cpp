#include <gtest/gtest.h>
#include "input.h"  // Assuming input.cpp is in the same directory

// Test suite for input functions
TEST(InputTest, GetStringInput) {
  string expectedInput = "John Doe";
  string actualInput = getStringInput("Enter your name");
  EXPECT_EQ(expectedInput, actualInput); // Check if entered name matches
}

TEST(InputTest, GetIntegerInputValid) {
  int expectedInput = 25;
  int actualInput = getIntegerInput("Enter a number (10-30): ", 10, 30);
  EXPECT_EQ(expectedInput, actualInput); // Check if entered number is within range
}

TEST(InputTest, GetIntegerInputInvalid) {
  EXPECT_DEATH(getIntegerInput("Enter a number: ", 0, 0), ""); // Test for invalid range (0-0)
  // You can also test for non-numeric input here
}

TEST(InputTest, GetCharInput) {
  char expectedInput = 'y';
  char actualInput = getCharInput("Enter (y/n): ");
  EXPECT_EQ(expectedInput, actualInput); // Check if entered character matches
}

