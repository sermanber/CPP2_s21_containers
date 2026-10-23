// #include "s21_set.hpp"
#include "test_all.hpp"
// #include "s21_multiset.hpp"
// #include "s21_vector.hpp"

//   bool operator==(const set<int>& lhs, const set<int>& rhs) {
//   if (lhs.size() != rhs.size()) return false;

//   auto it1 = lhs.begin();
//   auto it2 = rhs.begin();

//   while (it1 != lhs.end()) {
//     if (*it1 != *it2) return false;
//     ++it1;
//     ++it2;
//   }
//   return true;
// }

// bool operator<(const set<int>& lhs, const set<int>& rhs) {
//   auto it1 = lhs.begin();
//   auto it2 = rhs.begin();

//   while (it1 != lhs.end() && it2 != rhs.end()) {
//     if (*it1 < *it2) return true;
//     if (*it1 > *it2) return false;
//     ++it1;
//     ++it2;
//   }
//   return it1 == lhs.end() && it2 != rhs.end();
// }

TEST(VectorTest, DefaultConstructor) {
  s21_containers::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor) {
  s21_containers::vector<int> v(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, InitializerListConstructor) {
  s21_containers::vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyConstructor) {
  s21_containers::vector<int> original{1, 2, 3};
  s21_containers::vector<int> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(copy[i], original[i]);
  }
}

TEST(VectorTest, MoveConstructor) {
  s21_containers::vector<int> original{1, 2, 3};
  s21_containers::vector<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved[0], 1);
  EXPECT_TRUE(original.empty());
}

TEST(VectorTest, CopyAssignment) {
  s21_containers::vector<int> v1{1, 2, 3};
  s21_containers::vector<int> v2;
  v2 = v1;

  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, AtValidIndex) {
  s21_containers::vector<int> v{10, 20, 30};
  EXPECT_EQ(v.at(0), 10);
  EXPECT_EQ(v.at(2), 30);
}

TEST(VectorTest, AtInvalidIndex) {
  s21_containers::vector<int> v{1, 2, 3};
  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, FrontBack) {
  s21_containers::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, Data) {
  s21_containers::vector<int> v{1, 2, 3};
  int* data = v.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[2], 3);
}

TEST(VectorTest, Iterators) {
  s21_containers::vector<int> v{1, 2, 3};
  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);
}

TEST(VectorTest, ConstIterators) {
  const s21_containers::vector<int> v{1, 2, 3};
  int sum = 0;
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 6);
}

TEST(VectorTest, Empty) {
  s21_containers::vector<int> v1;
  EXPECT_TRUE(v1.empty());

  s21_containers::vector<int> v2{1};
  EXPECT_FALSE(v2.empty());
}

TEST(VectorTest, SizeCapacity) {
  s21_containers::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);

  v.push_back(1);
  EXPECT_EQ(v.size(), 1);
  EXPECT_GE(v.capacity(), 1);
}

TEST(VectorTest, MaxSize) {
  s21_containers::vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

TEST(VectorTest, Reserve) {
  s21_containers::vector<int> v;
  v.reserve(100);
  EXPECT_GE(v.capacity(), 100);
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, PushBack) {
  s21_containers::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBack) {
  s21_containers::vector<int> v{1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, Insert) {
  s21_containers::vector<int> v{1, 3, 4};
  auto it = v.insert(v.begin() + 1, 2);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, Erase) {
  s21_containers::vector<int> v{1, 2, 3, 4};
  v.erase(v.begin() + 1);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Swap) {
  s21_containers::vector<int> v1{1, 2, 3};
  s21_containers::vector<int> v2{4, 5};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, ShrinkToFit) {
  s21_containers::vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  v.pop_back();
  v.pop_back();

  size_t old_capacity = v.capacity();
  v.shrink_to_fit();

  EXPECT_EQ(v.capacity(), v.size());
  EXPECT_LT(v.capacity(), old_capacity);
}

TEST(VectorTest, Clear) {
  s21_containers::vector<int> v{1, 2, 3};
  v.clear();

  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, InsertMany) {
  s21_containers::vector<int> v{1, 5};
  v.insert_many(v.begin() + 1, 2, 3, 4);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, InsertManyBack) {
  s21_containers::vector<int> v{1, 2};
  v.insert_many_back(3, 4, 5);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, SelfAssignment) {
  s21_containers::vector<int> v{1, 2, 3};
  v = v;

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, LargeVector) {
  s21_containers::vector<int> v;
  const size_t count = 10000;

  for (size_t i = 0; i < count; ++i) {
    v.push_back(i);
  }

  EXPECT_EQ(v.size(), count);
  for (size_t i = 0; i < count; ++i) {
    EXPECT_EQ(v[i], i);
  }
}

TEST(VectorTest, ExceptionSafety) {
  s21_containers::vector<int> v{1, 2, 3};

  EXPECT_THROW(v.at(10), std::out_of_range);
  EXPECT_THROW(v.insert(v.begin() + 10, 4), std::out_of_range);
  EXPECT_THROW(v.erase(v.begin() + 10), std::out_of_range);
}

TEST(VectorTest, ConstAccess) {
  const s21_containers::vector<int> v{1, 2, 3};

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
  EXPECT_NE(v.data(), nullptr);
}

TEST(VectorTest, InsertAtEnd) {
  s21_containers::vector<int> v{1, 2};
  v.insert(v.end(), 3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertAtBegin) {
  s21_containers::vector<int> v{2, 3};
  v.insert(v.begin(), 1);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, EraseFromBegin) {
  s21_containers::vector<int> v{1, 2, 3};
  v.erase(v.begin());

  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, EraseFromEnd) {
  s21_containers::vector<int> v{1, 2, 3};
  v.erase(v.end() - 1);

  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, ReserveSmaller) {
  s21_containers::vector<int> v;
  v.reserve(10);
  size_t old_capacity = v.capacity();
  v.reserve(5);

  EXPECT_EQ(v.capacity(), old_capacity);
}

TEST(VectorTest, ShrinkToFitNoEffect) {
  s21_containers::vector<int> v{1, 2, 3};
  size_t old_capacity = v.capacity();
  v.shrink_to_fit();

  if (v.size() == old_capacity) {
    EXPECT_EQ(v.capacity(), old_capacity);
  }
}

TEST(VectorTest, InsertManyEmpty) {
  s21_containers::vector<int> v;
  v.insert_many(v.begin(), 1, 2, 3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertManyBackEmpty) {
  s21_containers::vector<int> v;
  v.insert_many_back(1, 2);

  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, MemoryLeakCheck) {
  {
    s21_containers::vector<int> v{1, 2, 3, 4, 5};
    v.push_back(6);
    v.pop_back();
    v.insert(v.begin(), 0);
    v.erase(v.end() - 1);
  }

  SUCCEED();
}

// ============================ ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ============================

template <typename T>
bool sets_equal(const set<T>& s1, const std::set<T>& s2) {
  if (s1.size() != s2.size()) return false;
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  while (it1 != s1.end() && it2 != s2.end()) {
    if (*it1 != *it2) return false;
    ++it1;
    ++it2;
  }
  return true;
}

template <typename T>
bool multisets_equal(const multiset<T>& ms1, const std::multiset<T>& ms2) {
  if (ms1.size() != ms2.size()) return false;
  auto it1 = ms1.begin();
  auto it2 = ms2.begin();
  while (it1 != ms1.end() && it2 != ms2.end()) {
    if (*it1 != *it2) return false;
    ++it1;
    ++it2;
  }
  return true;
}

// ============================ ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ SET
// ============================
TEST(SetTest, EmptyInitializerList) {
  set<int> set = {};
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, SingleElementInitializerList) {
  set<int> set = {42};
  EXPECT_EQ(set.size(), 1);
  EXPECT_TRUE(set.contains(42));
  EXPECT_EQ(*set.begin(), 42);
}

TEST(SetTest, ReverseOrderInsertion) {
  set<int> set;
  for (int i = 10; i >= 1; --i) {
    set.insert(i);
  }
  EXPECT_EQ(set.size(), 10);

  int expected = 1;
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(*it, expected);
    ++expected;
  }
}

TEST(SetTest, AlternateOrderInsertion) {
  set<int> set;
  set.insert(5);
  set.insert(3);
  set.insert(7);
  set.insert(1);
  set.insert(9);
  set.insert(4);
  set.insert(6);
  set.insert(2);
  set.insert(8);

  EXPECT_EQ(set.size(), 9);

  std::vector<int> elements;
  for (auto it = set.begin(); it != set.end(); ++it) {
    elements.push_back(*it);
  }

  for (size_t i = 1; i < elements.size(); ++i) {
    EXPECT_LT(elements[i - 1], elements[i]);
  }
}

TEST(SetTest, FindNonExistentElement) {
  set<int> set = {1, 2, 3, 4, 5};
  auto it = set.find(10);
  EXPECT_EQ(it, set.end());

  it = set.find(-1);
  EXPECT_EQ(it, set.end());

  it = set.find(0);
  EXPECT_EQ(it, set.end());
}

TEST(SetTest, EraseBeginIterator) {
  set<int> set = {1, 2, 3, 4, 5};
  auto it = set.begin();
  set.erase(it);

  EXPECT_EQ(set.size(), 4);
  EXPECT_FALSE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_TRUE(set.contains(4));
  EXPECT_TRUE(set.contains(5));
}

TEST(SetTest, EraseEndIterator) {
  set<int> set = {1, 2, 3};
  auto it = set.end();
  set.erase(it);
  EXPECT_EQ(set.size(), 3);
}

TEST(SetTest, EraseAllElements) {
  set<int> set = {1, 2, 3, 4, 5};

  while (!set.empty()) {
    auto it = set.begin();
    set.erase(it);
  }

  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, EraseAndReinsert) {
  set<int> set;

  for (int i = 0; i < 3; ++i) {
    set.insert(1);
    EXPECT_EQ(set.size(), 1);
    auto it = set.find(1);
    set.erase(it);
    EXPECT_TRUE(set.empty());
  }
}

TEST(SetTest, IteratorIncrementFromEnd) {
  set<int> set = {1, 2, 3};
  auto it = set.end();
  ++it;
  EXPECT_EQ(it, set.end());
}

TEST(SetTest, IteratorDecrementFromBegin) {
  set<int> set = {1, 2, 3};
  auto it = set.begin();
  --it;
  SUCCEED();
}

TEST(SetTest, ConstIteratorOperations) {
  const set<int> set = {1, 2, 3, 4, 5};

  auto it = set.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  auto it2 = it;
  EXPECT_EQ(*it2, 2);

  ++it2;
  EXPECT_EQ(*it2, 3);

  EXPECT_TRUE(it != it2);
  EXPECT_FALSE(it == it2);
}

TEST(SetTest, MaxSizeValue) {
  set<int> set;
  size_t max_size = set.max_size();
  EXPECT_GT(max_size, 0);
  EXPECT_LT(max_size, std::numeric_limits<size_t>::max());
}

TEST(SetTest, MergeEmptySet) {
  set<int> set1 = {1, 2, 3};
  set<int> set2;

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 3);
  EXPECT_TRUE(set2.empty());
}

TEST(SetTest, MergeIntoSelf) {
  set<int> set1 = {1, 2, 3};
  set1.merge(set1);

  EXPECT_EQ(set1.size(), 3);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
}

TEST(SetTest, SwapWithEmpty) {
  set<int> set1 = {1, 2, 3};
  set<int> set2;

  set1.swap(set2);

  EXPECT_TRUE(set1.empty());
  EXPECT_EQ(set2.size(), 3);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
}

TEST(SetTest, SwapWithSelf) {
  set<int> set1 = {1, 2, 3};
  set1.swap(set1);

  EXPECT_EQ(set1.size(), 3);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
}

TEST(SetTest, ClearEmptySet) {
  set<int> set;
  set.clear();

  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, InsertReturnValue) {
  set<int> set;

  auto result1 = set.insert(1);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(*result1.first, 1);

  auto result2 = set.insert(1);
  EXPECT_FALSE(result2.second);
  EXPECT_EQ(*result2.first, 1);

  auto result3 = set.insert(2);
  EXPECT_TRUE(result3.second);
  EXPECT_EQ(*result3.first, 2);
}

TEST(SetTest, LargeNumberOfElements) {
  set<int> set;
  const int COUNT = 10000;

  for (int i = 0; i < COUNT; ++i) {
    set.insert(i);
  }

  EXPECT_EQ(set.size(), COUNT);

  for (int i = 0; i < COUNT; ++i) {
    EXPECT_TRUE(set.contains(i));
  }

  int prev = -1;
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_GT(*it, prev);
    prev = *it;
  }
}

TEST(SetTest, StringSetOperations) {
  set<std::string> set;

  set.insert("apple");
  set.insert("banana");
  set.insert("cherry");
  set.insert("date");

  EXPECT_EQ(set.size(), 4);
  EXPECT_TRUE(set.contains("banana"));
  EXPECT_FALSE(set.contains("grape"));

  auto it = set.begin();
  EXPECT_EQ(*it, "apple");
  ++it;
  EXPECT_EQ(*it, "banana");
  ++it;
  EXPECT_EQ(*it, "cherry");
  ++it;
  EXPECT_EQ(*it, "date");

  auto found = set.find("banana");
  set.erase(found);
  EXPECT_EQ(set.size(), 3);
  EXPECT_FALSE(set.contains("banana"));
}

TEST(SetTest, DoubleSetOperations) {
  set<double> set;

  set.insert(3.14);
  set.insert(2.71);
  set.insert(1.41);
  set.insert(1.62);

  EXPECT_EQ(set.size(), 4);
  EXPECT_TRUE(set.contains(2.71));

  std::vector<double> elements;
  for (auto it = set.begin(); it != set.end(); ++it) {
    elements.push_back(*it);
  }

  for (size_t i = 1; i < elements.size(); ++i) {
    EXPECT_LT(elements[i - 1], elements[i]);
  }
}

TEST(SetTest, SetOfSets) {
  set<set<int>> set_of_sets;

  set<int> set1 = {1, 2, 3};
  set<int> set2 = {4, 5, 6};
  set<int> set3 = {7, 8, 9};

  set_of_sets.insert(set1);
  set_of_sets.insert(set2);
  set_of_sets.insert(set3);

  EXPECT_EQ(set_of_sets.size(), 3);

  auto found = set_of_sets.find(set1);
  EXPECT_NE(found, set_of_sets.end());
  EXPECT_TRUE(found->contains(1));
  EXPECT_TRUE(found->contains(2));
  EXPECT_TRUE(found->contains(3));
}

TEST(SetTest, IteratorStabilityAfterInsert) {
  set<int> set = {1, 2, 3};
  auto it = set.find(2);

  set.insert(4);
  set.insert(0);

  EXPECT_EQ(*it, 2);

  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(SetTest, IteratorStabilityAfterErase) {
  set<int> set = {1, 2, 3, 4};
  auto it = set.find(3);

  auto to_erase = set.find(2);
  set.erase(to_erase);

  EXPECT_EQ(*it, 3);

  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(SetTest, RedBlackTreePropertiesAfterComplexOperations) {
  set<int> set;

  std::vector<int> operations = {5, 3, 7, 2, 4, 6, 8, 1, 9, 0,
                                 5, 3, 7, 2, 4, 6, 8, 1, 9, 0};

  for (int op : operations) {
    if (op % 2 == 0) {
      set.insert(op);
    } else {
      auto it = set.find(op);
      if (it != set.end()) {
        set.erase(it);
      }
    }
  }

  std::vector<int> elements;
  for (auto it = set.begin(); it != set.end(); ++it) {
    elements.push_back(*it);
  }

  for (size_t i = 1; i < elements.size(); ++i) {
    EXPECT_LT(elements[i - 1], elements[i]);
  }

  for (size_t i = 1; i < elements.size(); ++i) {
    EXPECT_NE(elements[i - 1], elements[i]);
  }
}

TEST(SetTest, BoundaryValues) {
  set<int> set;

  set.insert(0);
  set.insert(std::numeric_limits<int>::max());
  set.insert(std::numeric_limits<int>::min());

  EXPECT_EQ(set.size(), 3);
  EXPECT_TRUE(set.contains(0));
  EXPECT_TRUE(set.contains(std::numeric_limits<int>::max()));
  EXPECT_TRUE(set.contains(std::numeric_limits<int>::min()));

  auto it = set.begin();
  EXPECT_EQ(*it, std::numeric_limits<int>::min());
  ++it;
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, std::numeric_limits<int>::max());
}

TEST(SetTest, MoveOperations) {
  set<int> set1 = {1, 2, 3, 4, 5};
  set<int> set2 = std::move(set1);

  EXPECT_TRUE(set1.empty());
  EXPECT_EQ(set2.size(), 5);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_TRUE(set2.contains(4));
  EXPECT_TRUE(set2.contains(5));

  set<int> set3;
  set3 = std::move(set2);

  EXPECT_TRUE(set2.empty());
  EXPECT_EQ(set3.size(), 5);
  EXPECT_TRUE(set3.contains(1));
  EXPECT_TRUE(set3.contains(2));
  EXPECT_TRUE(set3.contains(3));
  EXPECT_TRUE(set3.contains(4));
  EXPECT_TRUE(set3.contains(5));
}

TEST(SetTest, PrintMethodsDoNotCrash) {
  set<int> empty_set;
  empty_set.print();
  empty_set.printStructure();

  set<int> non_empty_set = {1, 2, 3, 4, 5};
  non_empty_set.print();
  non_empty_set.printStructure();

  SUCCEED();
}

TEST(SetTest, SearchMethod) {
  set<int> set = {1, 2, 3, 4, 5};

  EXPECT_TRUE(set.search(3));
  EXPECT_TRUE(set.search(1));
  EXPECT_TRUE(set.search(5));
  EXPECT_FALSE(set.search(0));
  EXPECT_FALSE(set.search(6));
  EXPECT_FALSE(set.search(10));
}

// ============================ ТЕСТЫ SET ============================

TEST(SetTest, DefaultConstructor) {
  set<int> set;
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, InitializerListConstructor) {
  set<int> set = {1, 2, 3, 4, 5};
  EXPECT_EQ(set.size(), 5);
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(3));
  EXPECT_TRUE(set.contains(5));
}

TEST(SetTest, CopyConstructor) {
  set<int> original = {1, 2, 3};
  set<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());
  EXPECT_TRUE(copy.contains(1));
  EXPECT_TRUE(copy.contains(2));
  EXPECT_TRUE(copy.contains(3));

  copy.insert(4);
  EXPECT_EQ(copy.size(), 4);
  EXPECT_EQ(original.size(), 3);
}

TEST(SetTest, MoveConstructor) {
  set<int> original = {1, 2, 3};
  set<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(moved.contains(1));
  EXPECT_TRUE(moved.contains(2));
  EXPECT_TRUE(moved.contains(3));
  EXPECT_TRUE(original.empty());
}

TEST(SetTest, MoveAssignment) {
  set<int> set1 = {1, 2};
  set<int> set2 = {3, 4};

  set1 = std::move(set2);

  EXPECT_EQ(set1.size(), 2);
  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set2.empty());
}

TEST(SetTest, Insert) {
  set<int> set;

  auto result1 = set.insert(1);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(*result1.first, 1);

  auto result2 = set.insert(2);
  EXPECT_TRUE(result2.second);
  EXPECT_EQ(*result2.first, 2);

  auto result3 = set.insert(1);
  EXPECT_FALSE(result3.second);
  EXPECT_EQ(*result3.first, 1);

  EXPECT_EQ(set.size(), 2);
}

TEST(SetTest, Erase) {
  set<int> set = {1, 2, 3, 4, 5};

  auto it = set.find(3);
  set.erase(it);
  EXPECT_EQ(set.size(), 4);
  EXPECT_FALSE(set.contains(3));

  it = set.find(10);
  set.erase(it);
  EXPECT_EQ(set.size(), 4);
}

TEST(SetTest, Clear) {
  set<int> set = {1, 2, 3, 4, 5};
  EXPECT_FALSE(set.empty());

  set.clear();
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, Swap) {
  set<int> set1 = {1, 2};
  set<int> set2 = {3, 4};

  set1.swap(set2);

  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
}

TEST(SetTest, Merge) {
  set<int> set1 = {1, 2, 3};
  set<int> set2 = {3, 4, 5};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 5);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(5));
  EXPECT_TRUE(set2.empty());
}

TEST(SetTest, IteratorBasic) {
  set<int> set = {3, 1, 4, 1, 5};

  std::vector<int> elements;
  for (auto it = set.begin(); it != set.end(); ++it) {
    elements.push_back(*it);
  }

  EXPECT_EQ(elements.size(), 4);
  EXPECT_EQ(elements[0], 1);
  EXPECT_EQ(elements[1], 3);
  EXPECT_EQ(elements[2], 4);
  EXPECT_EQ(elements[3], 5);
}

TEST(SetTest, ConstIterator) {
  const set<int> set = {1, 2, 3};

  std::vector<int> elements;
  for (auto it = set.begin(); it != set.end(); ++it) {
    elements.push_back(*it);
  }

  EXPECT_EQ(elements.size(), 3);
  EXPECT_EQ(elements[0], 1);
  EXPECT_EQ(elements[1], 2);
  EXPECT_EQ(elements[2], 3);
}

TEST(SetTest, IteratorOperations) {
  set<int> set = {1, 2, 3, 4, 5};

  auto it = set.find(3);
  EXPECT_EQ(*it, 3);

  ++it;
  EXPECT_EQ(*it, 4);

  --it;
  EXPECT_EQ(*it, 3);

  auto it2 = set.find(3);
  EXPECT_TRUE(it == it2);
  EXPECT_FALSE(it != it2);
}

TEST(SetTest, IteratorBeginEnd) {
  set<int> empty_set;
  EXPECT_EQ(empty_set.begin(), empty_set.end());

  set<int> set = {1};
  EXPECT_NE(set.begin(), set.end());
  EXPECT_EQ(*set.begin(), 1);
}

TEST(SetTest, Find) {
  set<int> set = {1, 2, 3, 4, 5};

  auto found = set.find(3);
  EXPECT_NE(found, set.end());
  EXPECT_EQ(*found, 3);

  auto not_found = set.find(10);
  EXPECT_EQ(not_found, set.end());
}

TEST(SetTest, Contains) {
  set<int> set = {1, 2, 3};

  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_FALSE(set.contains(4));
  EXPECT_FALSE(set.contains(0));
}

TEST(SetTest, Empty) {
  set<int> empty_set;
  EXPECT_TRUE(empty_set.empty());

  set<int> non_empty_set = {1};
  EXPECT_FALSE(non_empty_set.empty());

  non_empty_set.clear();
  EXPECT_TRUE(non_empty_set.empty());
}

TEST(SetTest, Size) {
  set<int> set;
  EXPECT_EQ(set.size(), 0);

  set.insert(1);
  EXPECT_EQ(set.size(), 1);

  set.insert(2);
  EXPECT_EQ(set.size(), 2);

  set.insert(2);
  EXPECT_EQ(set.size(), 2);

  set.erase(set.find(1));
  EXPECT_EQ(set.size(), 1);
}

TEST(SetTest, MaxSize) {
  set<int> set;
  EXPECT_GT(set.max_size(), 0);
}

TEST(SetTest, EmptySetOperations) {
  set<int> empty_set;

  EXPECT_EQ(empty_set.find(1), empty_set.end());
  EXPECT_FALSE(empty_set.contains(1));

  auto it = empty_set.find(1);
  empty_set.erase(it);

  EXPECT_EQ(empty_set.begin(), empty_set.end());
}

TEST(SetTest, SingleElementSet) {
  set<int> set = {42};

  EXPECT_EQ(set.size(), 1);
  EXPECT_TRUE(set.contains(42));
  EXPECT_EQ(*set.begin(), 42);

  set.erase(set.begin());
  EXPECT_TRUE(set.empty());
}

TEST(SetTest, DuplicateElements) {
  set<int> set;

  auto result1 = set.insert(1);
  EXPECT_TRUE(result1.second);

  auto result2 = set.insert(1);
  EXPECT_FALSE(result2.second);
  EXPECT_EQ(*result1.first, *result2.first);

  EXPECT_EQ(set.size(), 1);
}

TEST(SetTest, EraseComprehensive) {
  set<int> set;

  for (int i = 1; i <= 10; ++i) {
    set.insert(i);
  }
  EXPECT_EQ(set.size(), 10);

  set.erase(set.find(5));
  set.erase(set.find(3));
  set.erase(set.find(8));

  EXPECT_EQ(set.size(), 7);
  EXPECT_FALSE(set.contains(3));
  EXPECT_FALSE(set.contains(5));
  EXPECT_FALSE(set.contains(8));

  for (int i = 1; i <= 10; ++i) {
    if (i != 3 && i != 5 && i != 8) {
      EXPECT_TRUE(set.contains(i));
    }
  }
}

TEST(SetTest, EraseRootScenarios) {
  set<int> set;

  set.insert(3);
  set.insert(1);
  set.erase(set.find(3));
  EXPECT_EQ(set.size(), 1);
  EXPECT_TRUE(set.contains(1));

  set.clear();

  set.insert(1);
  set.insert(3);
  set.erase(set.find(1));
  EXPECT_EQ(set.size(), 1);
  EXPECT_TRUE(set.contains(3));

  set.clear();

  set.insert(2);
  set.insert(1);
  set.insert(3);
  set.erase(set.find(2));
  EXPECT_EQ(set.size(), 2);
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(3));
}

TEST(SetTest, LargeInsertAndFind) {
  set<int> set;
  const int COUNT = 1000;

  for (int i = 0; i < COUNT; ++i) {
    set.insert(i);
  }

  EXPECT_EQ(set.size(), COUNT);

  for (int i = 0; i < COUNT; ++i) {
    EXPECT_TRUE(set.contains(i));
  }

  EXPECT_FALSE(set.contains(-1));
  EXPECT_FALSE(set.contains(COUNT));
}

TEST(SetTest, RandomOperations) {
  set<int> set;
  std::set<int> std_set;

  for (int i = 0; i < 100; ++i) {
    int value = rand() % 50;

    if (rand() % 2) {
      set.insert(value);
      std_set.insert(value);
    } else {
      auto it = set.find(value);
      if (it != set.end()) {
        set.erase(it);
      }
      auto std_it = std_set.find(value);
      if (std_it != std_set.end()) {
        std_set.erase(std_it);
      }
    }

    EXPECT_EQ(set.size(), std_set.size());
  }
}

TEST(SetTest, RedBlackTreeInvariants) {
  set<int> set;

  std::vector<int> elements = {5, 3, 7, 2, 4, 6, 8, 1, 9, 0};
  for (int elem : elements) {
    set.insert(elem);
  }

  std::vector<int> result;
  for (auto it = set.begin(); it != set.end(); ++it) {
    result.push_back(*it);
  }

  for (size_t i = 1; i < result.size(); ++i) {
    EXPECT_LT(result[i - 1], result[i]);
  }

  for (int elem : elements) {
    EXPECT_TRUE(set.contains(elem));
  }
}

TEST(SetTest, RedBlackTreeAfterDeletion) {
  set<int> set;

  for (int i = 0; i < 20; ++i) {
    set.insert(i);
  }

  std::vector<int> to_delete = {5, 10, 15, 2, 8, 18};
  for (int elem : to_delete) {
    auto it = set.find(elem);
    if (it != set.end()) {
      set.erase(it);
    }
  }

  for (int elem : to_delete) {
    EXPECT_FALSE(set.contains(elem));
  }

  for (int i = 0; i < 20; ++i) {
    if (std::find(to_delete.begin(), to_delete.end(), i) == to_delete.end()) {
      EXPECT_TRUE(set.contains(i));
    }
  }

  std::vector<int> result;
  for (auto it = set.begin(); it != set.end(); ++it) {
    result.push_back(*it);
  }

  for (size_t i = 1; i < result.size(); ++i) {
    EXPECT_LT(result[i - 1], result[i]);
  }
}

TEST(SetTest, StringType) {
  set<std::string> set;

  set.insert("apple");
  set.insert("banana");
  set.insert("cherry");

  EXPECT_EQ(set.size(), 3);
  EXPECT_TRUE(set.contains("banana"));
  EXPECT_FALSE(set.contains("grape"));

  auto it = set.begin();
  EXPECT_EQ(*it, "apple");
  ++it;
  EXPECT_EQ(*it, "banana");
  ++it;
  EXPECT_EQ(*it, "cherry");
}

TEST(SetTest, DoubleType) {
  set<double> set;

  set.insert(3.14);
  set.insert(2.71);
  set.insert(1.41);

  EXPECT_EQ(set.size(), 3);
  EXPECT_TRUE(set.contains(2.71));

  std::vector<double> result;
  for (auto it = set.begin(); it != set.end(); ++it) {
    result.push_back(*it);
  }

  EXPECT_LT(result[0], result[1]);
  EXPECT_LT(result[1], result[2]);
}

TEST(SetTest, IteratorExceptions) {
  set<int> set;

  EXPECT_THROW(*set.end(), std::out_of_range);
  EXPECT_THROW(set.end().operator->(), std::out_of_range);

  set.insert(1);
  auto it = set.begin();
  set.erase(it);
}

// ============================ MULTISET TESTS ============================

TEST(MultisetTest, DefaultConstructor) {
  multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, InitializerListConstructor) {
  multiset<int> ms = {1, 2, 2, 3, 3, 3};
  EXPECT_EQ(ms.size(), 6);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 3);
}

TEST(MultisetTest, CopyConstructor) {
  multiset<int> original = {1, 2, 2, 3};
  multiset<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(copy.count(1), 1);
  EXPECT_EQ(copy.count(2), 2);
  EXPECT_EQ(copy.count(3), 1);

  copy.insert(4);
  EXPECT_EQ(copy.size(), 5);
  EXPECT_EQ(original.size(), 4);
}

TEST(MultisetTest, MoveConstructor) {
  multiset<int> original = {1, 2, 2, 3};
  multiset<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 4);
  EXPECT_EQ(moved.count(1), 1);
  EXPECT_EQ(moved.count(2), 2);
  EXPECT_EQ(moved.count(3), 1);
  EXPECT_TRUE(original.empty());
}

TEST(MultisetTest, InsertDuplicates) {
  multiset<int> ms;

  auto result1 = ms.insert(1);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(*result1.first, 1);

  auto result2 = ms.insert(1);
  EXPECT_TRUE(result2.second);
  EXPECT_EQ(*result2.first, 1);

  auto result3 = ms.insert(1);
  EXPECT_TRUE(result3.second);
  EXPECT_EQ(*result3.first, 1);

  EXPECT_EQ(ms.size(), 3);
  EXPECT_EQ(ms.count(1), 3);
}

TEST(MultisetTest, Count) {
  multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};

  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 3);
  EXPECT_EQ(ms.count(4), 4);
  EXPECT_EQ(ms.count(5), 0);
}

TEST(MultisetTest, EraseAllOccurrences) {
  multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};

  size_t removed = ms.erase(3);
  EXPECT_EQ(removed, 3);
  EXPECT_EQ(ms.size(), 7);
  EXPECT_EQ(ms.count(3), 0);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(4));

  removed = ms.erase(5);
  EXPECT_EQ(removed, 0);
  EXPECT_EQ(ms.size(), 7);
}

TEST(MultisetTest, LowerBound) {
  multiset<int> ms = {1, 2, 2, 3, 4, 4, 4, 5};

  auto lb1 = ms.lower_bound(2);
  EXPECT_NE(lb1, ms.end());
  EXPECT_EQ(*lb1, 2);

  auto lb2 = ms.lower_bound(3);
  EXPECT_NE(lb2, ms.end());
  EXPECT_EQ(*lb2, 3);

  auto lb3 = ms.lower_bound(0);
  EXPECT_NE(lb3, ms.end());
  EXPECT_EQ(*lb3, 1);

  auto lb4 = ms.lower_bound(6);
  EXPECT_EQ(lb4, ms.end());
}

TEST(MultisetTest, UpperBound) {
  multiset<int> ms = {1, 2, 2, 3, 4, 4, 4, 5};

  auto ub1 = ms.upper_bound(2);
  EXPECT_NE(ub1, ms.end());
  EXPECT_EQ(*ub1, 3);

  auto ub2 = ms.upper_bound(4);
  EXPECT_NE(ub2, ms.end());
  EXPECT_EQ(*ub2, 5);

  auto ub3 = ms.upper_bound(5);
  EXPECT_EQ(ub3, ms.end());

  auto ub4 = ms.upper_bound(0);
  EXPECT_NE(ub4, ms.end());
  EXPECT_EQ(*ub4, 1);
}

TEST(MultisetTest, EqualRange) {
  multiset<int> ms = {1, 2, 2, 3, 4, 4, 4, 5};

  auto range1 = ms.equal_range(2);
  std::vector<int> result1;
  for (auto it = range1.first; it != range1.second; ++it) {
    result1.push_back(*it);
  }
  EXPECT_EQ(result1.size(), 2);
  EXPECT_EQ(result1[0], 2);
  EXPECT_EQ(result1[1], 2);

  auto range2 = ms.equal_range(4);
  std::vector<int> result2;
  for (auto it = range2.first; it != range2.second; ++it) {
    result2.push_back(*it);
  }
  EXPECT_EQ(result2.size(), 3);
  EXPECT_EQ(result2[0], 4);
  EXPECT_EQ(result2[1], 4);
  EXPECT_EQ(result2[2], 4);

  auto range3 = ms.equal_range(6);
  EXPECT_EQ(range3.first, range3.second);
  EXPECT_EQ(range3.first, ms.upper_bound(6));
}

TEST(MultisetTest, IteratorWithDuplicates) {
  multiset<int> ms = {3, 1, 2, 2, 1, 3, 3};

  std::vector<int> elements;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    elements.push_back(*it);
  }

  std::vector<int> expected = {1, 1, 2, 2, 3, 3, 3};
  EXPECT_EQ(elements, expected);
}

TEST(MultisetTest, ConstIterator) {
  const multiset<int> ms = {1, 2, 2, 3};

  std::vector<int> elements;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    elements.push_back(*it);
  }

  EXPECT_EQ(elements.size(), 4);
  EXPECT_EQ(elements[0], 1);
  EXPECT_EQ(elements[1], 2);
  EXPECT_EQ(elements[2], 2);
  EXPECT_EQ(elements[3], 3);
}

TEST(MultisetTest, Find) {
  multiset<int> ms = {1, 2, 2, 3, 3, 3};

  auto found = ms.find(2);
  EXPECT_NE(found, ms.end());
  EXPECT_EQ(*found, 2);

  auto first = ms.find(3);
  EXPECT_NE(first, ms.end());
  EXPECT_EQ(*first, 3);

  auto not_found = ms.find(5);
  EXPECT_EQ(not_found, ms.end());
}

TEST(MultisetTest, Contains) {
  multiset<int> ms = {1, 2, 2, 3};

  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_FALSE(ms.contains(4));
  EXPECT_FALSE(ms.contains(0));
}

TEST(MultisetTest, Clear) {
  multiset<int> ms = {1, 2, 2, 3, 3, 3};
  EXPECT_FALSE(ms.empty());

  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, Swap) {
  multiset<int> ms1 = {1, 2, 2};
  multiset<int> ms2 = {3, 3, 4, 4};

  ms1.swap(ms2);

  EXPECT_EQ(ms1.size(), 4);
  EXPECT_EQ(ms1.count(3), 2);
  EXPECT_EQ(ms1.count(4), 2);

  EXPECT_EQ(ms2.size(), 3);
  EXPECT_EQ(ms2.count(1), 1);
  EXPECT_EQ(ms2.count(2), 2);
}

TEST(MultisetTest, LargeMultiset) {
  multiset<int> ms;
  const int COUNT = 1000;

  for (int i = 0; i < COUNT; ++i) {
    ms.insert(i % 100);
  }

  EXPECT_EQ(ms.size(), COUNT);

  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(ms.count(i), 10);
  }
}

TEST(MultisetTest, StringMultiset) {
  multiset<std::string> ms;

  ms.insert("apple");
  ms.insert("banana");
  ms.insert("apple");
  ms.insert("cherry");
  ms.insert("banana");
  ms.insert("apple");

  EXPECT_EQ(ms.size(), 6);
  EXPECT_EQ(ms.count("apple"), 3);
  EXPECT_EQ(ms.count("banana"), 2);
  EXPECT_EQ(ms.count("cherry"), 1);

  std::vector<std::string> elements;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    elements.push_back(*it);
  }

  for (size_t i = 1; i < elements.size(); ++i) {
    EXPECT_LE(elements[i - 1], elements[i]);
  }
}

TEST(MultisetTest, RedBlackTreeInvariantsWithDuplicates) {
  multiset<int> ms;

  std::vector<int> elements = {5, 3, 7, 3, 2, 5, 4, 7, 1, 5, 0, 3};
  for (int elem : elements) {
    ms.insert(elem);
  }

  std::vector<int> result;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    result.push_back(*it);
  }

  for (size_t i = 1; i < result.size(); ++i) {
    EXPECT_LE(result[i - 1], result[i]);
  }

  EXPECT_EQ(ms.count(3), 3);
  EXPECT_EQ(ms.count(5), 3);
  EXPECT_EQ(ms.count(7), 2);
}

TEST(MultisetTest, ComparisonWithStdMultiset) {
  multiset<int> my_ms;
  std::multiset<int> std_ms;

  for (int i = 0; i < 100; ++i) {
    int value = rand() % 20;
    my_ms.insert(value);
    std_ms.insert(value);
  }

  EXPECT_EQ(my_ms.size(), std_ms.size());

  auto my_it = my_ms.begin();
  auto std_it = std_ms.begin();
  while (my_it != my_ms.end() && std_it != std_ms.end()) {
    EXPECT_EQ(*my_it, *std_it);
    ++my_it;
    ++std_it;
  }
}

TEST(MultisetTest, IteratorStability) {
  multiset<int> ms = {1, 2, 2, 3, 3, 3};

  auto it1 = ms.find(2);
  auto it2 = ms.find(3);

  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 3);

  ms.insert(4);
  ms.insert(2);

  EXPECT_EQ(*it1, 2);
  EXPECT_EQ(*it2, 3);
}

// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }