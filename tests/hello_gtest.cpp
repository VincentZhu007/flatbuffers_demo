//
// Created by zgd on 2023/1/7.
//

#include <iostream>
#include <gtest/gtest.h>

class HelloTest : public ::testing::Test {
 public:
  void SetUp() override {
    std::cout << "Set up test case..." << std::endl;
  }
  void TearDown() override {
    std::cout << "Tear down test case..." << std::endl;
  }
};

TEST_F(HelloTest, Simple) {
  ASSERT_EQ(2 + 3, 5);
}
