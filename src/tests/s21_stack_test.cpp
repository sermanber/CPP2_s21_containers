#include "test_all.hpp"

using s21_containers::stack;

TEST(StackTest, DefaultConstructor) {
  stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
  stack<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, CopyConstructor) {
  stack<int> s1 = {10, 20, 30};
  stack<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s2.top(), 30);
  s1.pop();
  EXPECT_NE(s1.size(), s2.size());
}

TEST(StackTest, MoveConstructor) {
  stack<int> s1 = {5, 10, 15};
  stack<int> s2(std::move(s1));
  EXPECT_EQ(s2.top(), 15);
  EXPECT_TRUE(s1.empty());
}

TEST(StackTest, CopyAssignment) {
  stack<int> s1 = {1, 2, 3};
  stack<int> s2;
  s2 = s1;
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
  s1.pop();
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, MoveAssignment) {
  stack<int> s1 = {1, 2, 3};
  stack<int> s2;
  s2 = std::move(s1);
  EXPECT_EQ(s2.top(), 3);
  EXPECT_TRUE(s1.empty());
}

TEST(StackTest, PushAndTop) {
  stack<std::string> s;
  s.push("Hello");
  s.push("World");
  EXPECT_EQ(s.top(), "World");
  s.pop();
  EXPECT_EQ(s.top(), "Hello");
}

TEST(StackTest, PopThrowsOnEmpty) {
  stack<int> s;
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(StackTest, TopThrowsOnEmpty) {
  stack<int> s;
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(StackTest, SizeAndEmpty) {
  stack<int> s;
  EXPECT_TRUE(s.empty());
  s.push(10);
  s.push(20);
  EXPECT_EQ(s.size(), 2);
  s.pop();
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.empty());
}

TEST(StackTest, Clear) {
  stack<int> s = {1, 2, 3, 4};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, Swap) {
  stack<int> s1 = {1, 2, 3};
  stack<int> s2 = {9, 8};
  s1.swap(s2);
  EXPECT_EQ(s1.top(), 8);
  EXPECT_EQ(s2.top(), 3);
  EXPECT_EQ(s1.size(), 2);
  EXPECT_EQ(s2.size(), 3);
}

TEST(StackTest, InsertManyBack) {
  stack<int> s;
  s.insert_many_back(10, 20, 30);
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 30);
  s.pop();
  EXPECT_EQ(s.top(), 20);
}

TEST(StackTest, CopyAndModifyIndependently) {
  stack<int> s1 = {1, 2, 3};
  stack<int> s2(s1);
  s1.pop();
  EXPECT_EQ(s1.top(), 2);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, MultiplePushPop) {
  stack<int> s;
  for (int i = 0; i < 100; ++i) s.push(i);
  EXPECT_EQ(s.size(), 100);
  for (int i = 99; i >= 0; --i) {
    EXPECT_EQ(s.top(), i);
    s.pop();
  }
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, PushDifferentTypes) {
  stack<double> s1;
  s1.push(3.14);
  s1.push(2.71);
  EXPECT_NEAR(s1.top(), 2.71, 1e-7);
  s1.pop();
  EXPECT_NEAR(s1.top(), 3.14, 1e-7);
}
