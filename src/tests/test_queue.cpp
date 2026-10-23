// #include "../src/s21_queue.h"
// #include <gtest/gtest.h>
// #include <string>

// using namespace s21_containers;

#include "test_all.hpp"
// #include "../s21_containers.hpp"

/* === Тесты конструкторов === */

TEST(QueueTest, DefaultConstructor) {
  queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0u);
}

TEST(QueueTest, InitListConstructor) {
  queue<int> q{1, 2, 3, 4};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 4u);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 4);
}

TEST(QueueTest, CopyConstructor) {
  queue<int> q1{10, 20, 30};
  queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3u);
  EXPECT_EQ(q2.front(), 10);
  q2.pop();
  EXPECT_EQ(q2.front(), 20);
  EXPECT_EQ(q1.front(), 10);
}

TEST(QueueTest, MoveConstructor) {
  queue<int> q1{7, 8, 9};
  queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3u);
  EXPECT_EQ(q2.front(), 7);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, DestructorSafety) {
  queue<int> *q = new queue<int>();
  q->push(42);
  delete q;
  SUCCEED();
}

/* === Тесты операторов присваивания === */

TEST(QueueTest, CopyAssignment) {
  queue<int> q1{1, 2};
  queue<int> q2;
  q2 = q1;
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 1);
  q2.pop();
  EXPECT_EQ(q2.front(), 2);
  EXPECT_EQ(q1.front(), 1);
}

TEST(QueueTest, MoveAssignment) {
  queue<int> q1{5, 6};
  queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 5);
  EXPECT_TRUE(q1.empty());
}

/* === Тесты доступа к элементам === */

TEST(QueueTest, Front) {
  queue<int> q{100, 200};
  EXPECT_EQ(q.front(), 100);
}

TEST(QueueTest, Back) {
  queue<int> q{100, 200};
  EXPECT_EQ(q.back(), 200);
}

TEST(QueueTest, FrontException) {
  queue<int> q;
  EXPECT_THROW(q.front(), std::out_of_range);
}

TEST(QueueTest, BackException) {
  queue<int> q;
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, PopException) {
  queue<int> q;
  EXPECT_THROW(q.pop(), std::out_of_range);
}

/* === Тесты ёмкости === */

TEST(QueueTest, EmptyAndSize) {
  queue<int> q;
  EXPECT_TRUE(q.empty());
  q.push(1);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 1u);
}

/* === Тесты модификаторов === */

TEST(QueueTest, PushPop) {
  queue<int> q;
  q.push(10);
  q.push(20);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 20);
  EXPECT_EQ(q.size(), 2u);
  q.pop();
  EXPECT_EQ(q.front(), 20);
  EXPECT_EQ(q.size(), 1u);
}

TEST(QueueTest, Swap) {
  queue<int> q1{1, 2};
  queue<int> q2{9};
  q1.swap(q2);
  EXPECT_EQ(q1.front(), 9);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q1.size(), 1u);
  EXPECT_EQ(q2.size(), 2u);
}

TEST(QueueTest, InsertManyBack) {
  queue<int> q;
  q.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(q.size(), 5u);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 5);

  q.pop();
  EXPECT_EQ(q.front(), 2);
}

TEST(QueueTest, DoubleType) {
  queue<double> q;
  q.push(3.14);
  q.push(2.71);
  EXPECT_NEAR(q.front(), 3.14, 1e-9);
  EXPECT_NEAR(q.back(), 2.71, 1e-9);
  EXPECT_EQ(q.size(), 2u);
}

TEST(QueueTest, StringType) {
  queue<std::string> q;
  q.push("hello");
  q.push("world");
  EXPECT_EQ(q.front(), "hello");
  EXPECT_EQ(q.back(), "world");
  q.pop();
  EXPECT_EQ(q.front(), "world");
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
