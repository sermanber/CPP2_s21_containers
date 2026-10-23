// #include "../src_plus/s21_array.h"
// #include <gtest/gtest.h>
// using namespace s21_containers;
#include "test_all.hpp"
/* === Тесты конструкторов === */
TEST(ArrayConstructorTest, DefaultConstructor) {
  array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}
TEST(ArrayConstructorTest, InitializerList) {
  array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}
TEST(ArrayConstructorTest, InitializerListTooManyElements) {
  EXPECT_THROW((array<int, 2>{1, 2, 3}), std::length_error);
}
TEST(ArrayConstructorTest, CopyConstructor) {
  array<int, 3> arr1 = {4, 5, 6};
  array<int, 3> arr2(arr1);
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}
TEST(ArrayConstructorTest, MoveConstructor) {
  array<int, 3> arr1 = {7, 8, 9};
  array<int, 3> arr2(std::move(arr1));
  EXPECT_EQ(arr2[0], 7);
  EXPECT_EQ(arr2[1], 8);
  EXPECT_EQ(arr2[2], 9);
}
/* === Тесты операторов присваивания === */
TEST(ArrayOperatorTest, CopyAssignment) {
  array<int, 3> arr1 = {10, 11, 12};
  array<int, 3> arr2;
  arr2 = arr1;
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}
TEST(ArrayOperatorTest, MoveAssignment) {
  array<int, 3> arr1 = {13, 14, 15};
  array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2[0], 13);
  EXPECT_EQ(arr2[1], 14);
  EXPECT_EQ(arr2[2], 15);
}
/* === Тесты доступа к элементам === */
TEST(ArrayAccessTest, AtValid) {
  array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
}
TEST(ArrayAccessTest, AtOutOfRange) {
  array<int, 3> arr = {1, 2, 3};
  EXPECT_THROW(arr.at(5), std::out_of_range);
}
TEST(ArrayAccessTest, OperatorBrackets) {
  array<int, 3> arr = {4, 5, 6};
  EXPECT_EQ(arr[0], 4);
  EXPECT_EQ(arr[2], 6);
}
TEST(ArrayAccessTest, FrontBack) {
  array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 3);
}
TEST(ArrayAccessTest, DataPointer) {
  array<int, 3> arr = {1, 2, 3};
  const int *ptr = arr.data();
  EXPECT_EQ(ptr[1], 2);
}
/* === Тесты итераторов === */
TEST(ArrayIteratorTest, BeginEnd) {
  array<int, 3> arr = {1, 2, 3};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(*(arr.end() - 1), 3);
}
TEST(ArrayIteratorTest, ConstBeginEnd) {
  const array<int, 3> arr = {4, 5, 6};
  const int *it = arr.cbegin();
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(*(arr.cend() - 1), 6);
}
/* === Тесты ёмкости === */
TEST(ArrayCapacityTest, EmptySizeMaxSize) {
  array<int, 0> arr0;
  EXPECT_TRUE(arr0.empty());
  EXPECT_EQ(arr0.size(), 0);
  array<int, 5> arr5;
  EXPECT_FALSE(arr5.empty());
  EXPECT_EQ(arr5.size(), 5);
  EXPECT_EQ(arr5.max_size(), 5);
}
/* === Тесты модификаторов === */
TEST(ArrayModifiersTest, Fill) {
  array<int, 4> arr;
  arr.fill(42);
  for (auto &el : arr) {
    EXPECT_EQ(el, 42);
  }
}
TEST(ArrayModifiersTest, Swap) {
  array<int, 3> arr1 = {1, 2, 3};
  array<int, 3> arr2 = {7, 8, 9};
  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 7);
  EXPECT_EQ(arr2[0], 1);
}
// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }