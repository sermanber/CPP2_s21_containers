
#include "test_all.hpp"

using s21_containers::list;

template <class T>
static std::vector<T> Collect(const list<T>& L) {
  std::vector<T> v;
  for (auto it = L.begin(); it != L.end(); ++it) v.push_back(*it);
  return v;
}

TEST(List_Ctors, DefaultAndSizeCtor) {
  list<int> a;
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0u);

  list<int> b(3);
  EXPECT_FALSE(b.empty());
  EXPECT_EQ(b.size(), 3u);
  auto vec = Collect(b);
  EXPECT_EQ(vec, (std::vector<int>{0, 0, 0}));
}

TEST(List_Ctors, InitListCopyMoveAssign) {
  list<int> a{1, 2, 3};
  EXPECT_EQ(Collect(a), (std::vector<int>{1, 2, 3}));

  list<int> b(a);
  EXPECT_EQ(Collect(b), (std::vector<int>{1, 2, 3}));

  list<int> c(std::move(b));
  EXPECT_EQ(Collect(c), (std::vector<int>{1, 2, 3}));
  EXPECT_TRUE(b.empty());

  list<int> d;
  list<int> e{9, 8};
  d = e;
  EXPECT_EQ(Collect(d), (std::vector<int>{9, 8}));

  list<int> f{7};
  d = std::move(f);
  EXPECT_EQ(Collect(d), (std::vector<int>{7}));
  EXPECT_TRUE(f.empty());
}

TEST(List_Access, FrontBackAndExceptions) {
  list<int> e;
  EXPECT_THROW(e.front(), std::out_of_range);
  EXPECT_THROW(e.back(), std::out_of_range);

  list<int> a{10};
  EXPECT_EQ(a.front(), 10);
  EXPECT_EQ(a.back(), 10);

  const list<int> ca{1, 2};
  EXPECT_EQ(ca.front(), 1);
  EXPECT_EQ(ca.back(), 2);
}

TEST(List_Iterators, IncDecAndConst) {
  list<int> a{1, 2, 3};
  auto it = a.begin();
  EXPECT_EQ(*it, 1);
  auto it2 = it++;
  EXPECT_EQ(*it2, 1);
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  auto it3 = it--;
  EXPECT_EQ(*it3, 3);
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);

  list<int>::const_iterator cit = a.begin();
  EXPECT_EQ(*cit, 1);
  ++cit;
  EXPECT_EQ(*cit, 2);
  --cit;
  EXPECT_EQ(*cit, 1);

  EXPECT_TRUE(a.begin() != a.end());
  auto e = a.end();
  --e;
  EXPECT_EQ(*e, 3);
}

TEST(List_Capacity, EmptySizeMaxSize) {
  list<int> a;
  EXPECT_TRUE(a.empty());
  EXPECT_GT(a.max_size(), 0u);
  a.push_back(1);
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.size(), 1u);
}

TEST(List_Modifiers, ClearInsertEraseEnd) {
  list<int> a{1, 3};

  auto it = a.insert(a.begin(), 0);
  EXPECT_EQ(*it, 0);

  int x = 4;
  it = a.insert(a.end(), std::move(x));
  EXPECT_EQ(*it, 4);

  auto beg = a.begin();
  ++beg;
  a.erase(beg);
  EXPECT_EQ(Collect(a), (std::vector<int>{0, 3, 4}));

  auto before = a.size();
  a.erase(a.end());
  EXPECT_EQ(a.size(), before);

  a.clear();
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0u);
}

TEST(List_Modifiers, PushPopFrontBackEmptyAndNot) {
  list<int> a;

  a.pop_back();
  a.pop_front();
  EXPECT_TRUE(a.empty());

  a.push_back(2);
  a.push_front(1);
  a.push_back(3);
  EXPECT_EQ(Collect(a), (std::vector<int>{1, 2, 3}));

  a.pop_front();
  EXPECT_EQ(Collect(a), (std::vector<int>{2, 3}));
  a.pop_back();
  EXPECT_EQ(Collect(a), (std::vector<int>{2}));
}

TEST(List_Modifiers, Swap) {
  list<int> a{1, 2}, b{7};
  a.swap(b);
  EXPECT_EQ(Collect(a), (std::vector<int>{7}));
  EXPECT_EQ(Collect(b), (std::vector<int>{1, 2}));
}

TEST(List_Algorithms, MergeNormalAndEarlyReturns) {
  list<int> a{1, 3, 5};
  list<int> b{0, 2, 4, 6};
  a.merge(b);
  EXPECT_TRUE(b.empty());
  EXPECT_EQ(Collect(a), (std::vector<int>{0, 1, 2, 3, 4, 5, 6}));

  list<int> c;
  a.merge(c);
  EXPECT_TRUE(c.empty());
  EXPECT_EQ(a.size(), 7u);

  size_t before = a.size();
  a.merge(a);
  EXPECT_EQ(a.size(), before);
}

TEST(List_Algorithms, SpliceNormalEmptySelf) {
  list<int> a{1, 2, 3};
  list<int> b{9, 9};

  auto pos = a.begin();
  ++pos;
  a.splice(pos, b);
  EXPECT_TRUE(b.empty());
  EXPECT_EQ(Collect(a), (std::vector<int>{1, 9, 9, 2, 3}));

  list<int> c;
  a.splice(a.begin(), c);
  EXPECT_TRUE(c.empty());
  EXPECT_EQ(Collect(a), (std::vector<int>{1, 9, 9, 2, 3}));

  size_t before = a.size();
  a.splice(a.end(), a);
  EXPECT_EQ(a.size(), before);
}

TEST(List_Algorithms, ReverseSmallAndBig) {
  list<int> a;
  a.reverse();
  EXPECT_TRUE(a.empty());

  list<int> b{42};
  b.reverse();
  EXPECT_EQ(Collect(b), (std::vector<int>{42}));

  list<int> c{1, 2, 3, 4};
  c.reverse();
  EXPECT_EQ(Collect(c), (std::vector<int>{4, 3, 2, 1}));
}

TEST(List_Algorithms, UniqueSmallAndWithDuplicates) {
  list<int> a;
  a.unique();
  EXPECT_TRUE(a.empty());

  list<int> b{5};
  b.unique();
  EXPECT_EQ(Collect(b), (std::vector<int>{5}));

  list<int> c{1, 1, 2, 2, 2, 3, 3, 4, 5, 5};
  c.unique();
  EXPECT_EQ(Collect(c), (std::vector<int>{1, 2, 3, 4, 5}));

  list<int> d{1, 2, 1};
  d.unique();
  EXPECT_EQ(Collect(d), (std::vector<int>{1, 2, 1}));
}

TEST(List_Algorithms, SortBranches) {
  list<int> a;
  a.sort();
  EXPECT_TRUE(a.empty());

  list<int> b{2};
  b.sort();
  EXPECT_EQ(Collect(b), (std::vector<int>{2}));

  list<int> c{4, 1, 3, 2, 0, 5, 2, 2, -1};
  c.sort();
  EXPECT_EQ(Collect(c), (std::vector<int>{-1, 0, 1, 2, 2, 2, 3, 4, 5}));

  list<int> d{-3, -2, -1, 0, 1, 2, 3};
  d.sort();
  EXPECT_EQ(Collect(d), (std::vector<int>{-3, -2, -1, 0, 1, 2, 3}));
}

using s21_containers::map;

template <class K, class V>
static std::vector<std::pair<K, V>> Collect(map<K, V>& M) {
  std::vector<std::pair<K, V>> out;
  for (auto it = M.begin(); it != M.end(); ++it) out.push_back(*it);
  return out;
}

TEST(Map_Ctors, DefaultAndInitList) {
  map<int, std::string> A;
  EXPECT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0u);

  map<int, std::string> B{{2, "two"}, {1, "one"}, {3, "three"}};
  EXPECT_FALSE(B.empty());
  EXPECT_EQ(B.size(), 3u);

  auto vec = Collect(B);
  EXPECT_EQ(vec.size(), 3u);
  EXPECT_EQ(vec[0].first, 1);
  EXPECT_EQ(vec[1].first, 2);
  EXPECT_EQ(vec[2].first, 3);
}

TEST(Map_Ctors, CopyMoveAssign) {
  map<int, int> A{{2, 2}, {1, 1}, {3, 3}};

  map<int, int> B(A);
  EXPECT_EQ(B.size(), 3u);
  EXPECT_EQ(B.at(1), 1);

  map<int, int> C(std::move(B));
  EXPECT_EQ(C.size(), 3u);
  EXPECT_TRUE(B.empty());
  map<int, int> D;
  D = A;
  EXPECT_EQ(D.size(), 3u);
  EXPECT_EQ(D.at(3), 3);

  map<int, int> E;
  E = std::move(D);
  EXPECT_EQ(E.size(), 3u);
  EXPECT_TRUE(D.empty());
}

TEST(Map_Iters, IterateForwardAndBackward) {
  map<int, char> M{{2, 'b'}, {1, 'a'}, {3, 'c'}};

  auto it = M.begin();
  ASSERT_NE(it, M.end());
  EXPECT_EQ(it->first, 1);
  ++it;
  EXPECT_EQ(it->first, 2);
  it++;
  EXPECT_EQ((--it)->first, 2);

  int last = 0;
  for (auto i = M.begin(); i != M.end(); ++i) last = i->first;
  EXPECT_EQ(last, 3);
  map<int, int> E;
  EXPECT_EQ(E.begin(), E.end());
}
TEST(Map_Capacity, EmptySizeMaxSize) {
  map<int, int> M;
  EXPECT_TRUE(M.empty());
  EXPECT_GT(M.max_size(), 0u);
  M.insert({1, 10});
  EXPECT_FALSE(M.empty());
  EXPECT_EQ(M.size(), 1u);
}

TEST(Map_Access, AtAndBrackets) {
  map<std::string, int> M;
  M.insert({"x", 5});
  EXPECT_EQ(M.at("x"), 5);
  EXPECT_THROW(M.at("nope"), std::out_of_range);

  const map<std::string, int>& CM = M;
  EXPECT_EQ(CM.at("x"), 5);
  EXPECT_THROW(CM.at("nope"), std::out_of_range);

  M["y"] += 7;
  EXPECT_EQ(M.at("y"), 7);
  M["x"] = 42;
  EXPECT_EQ(M.at("x"), 42);
}

TEST(Map_Modifiers, InsertVariantsAndDuplicate) {
  map<int, int> M;

  auto [it1, ok1] = M.insert({2, 20});
  EXPECT_TRUE(ok1);
  EXPECT_EQ(it1->second, 20);

  auto [it2, ok2] = M.insert(1, 10);
  EXPECT_TRUE(ok2);
  EXPECT_EQ(it2->first, 1);

  auto [it3, ok3] = M.insert({2, 999});
  EXPECT_FALSE(ok3);
  EXPECT_EQ(it3->second, 20);

  auto [it4, ok4] = M.insert_or_assign(3, 30);
  EXPECT_TRUE(ok4);
  auto [it5, ok5] = M.insert_or_assign(3, 33);
  EXPECT_FALSE(ok5);
  EXPECT_EQ(it5->second, 33);

  EXPECT_EQ(M.size(), 3u);
}

TEST(Map_Modifiers, EraseIteratorKeyClearSwap) {
  map<int, int> M{{20, 1}, {10, 2}, {30, 3}, {25, 4}, {40, 5}};

  size_t before = M.size();
  M.erase(M.end());
  EXPECT_EQ(M.size(), before);

  auto it = M.begin();
  M.erase(it);
  EXPECT_FALSE(M.contains(10));
  EXPECT_EQ(M.size(), before - 1);

  EXPECT_EQ(M.erase(30), 1u);
  EXPECT_FALSE(M.contains(30));
  EXPECT_EQ(M.size(), before - 2);

  EXPECT_EQ(M.erase(777), 0u);

  M.clear();
  EXPECT_TRUE(M.empty());

  map<int, int> A{{1, 1}}, B{{2, 2}, {3, 3}};
  A.swap(B);
  EXPECT_TRUE(A.contains(2));
  EXPECT_TRUE(B.contains(1));
  EXPECT_EQ(A.size(), 2u);
  EXPECT_EQ(B.size(), 1u);
}

TEST(Map_Modifiers, MergeMoveAndConflicts) {
  map<std::string, int> A{{"a", 1}, {"c", 3}};
  map<std::string, int> B{{"b", 2}, {"d", 4}};
  A.merge(B);
  EXPECT_EQ(A.size(), 4u);
  EXPECT_TRUE(B.empty());
  EXPECT_TRUE(A.contains("a") && A.contains("b") && A.contains("c") &&
              A.contains("d"));

  map<std::string, int> C{{"x", 10}, {"y", 20}};
  map<std::string, int> D{{"y", 999}, {"z", 30}};
  C.merge(D);
  EXPECT_EQ(C.size(), 3u);
  EXPECT_TRUE(D.contains("y"));
  EXPECT_FALSE(D.contains("z"));
}

TEST(Map_Lookup, Contains) {
  map<int, int> M;
  EXPECT_FALSE(M.contains(1));
  M.insert({1, 1});
  EXPECT_TRUE(M.contains(1));
}

TEST(Map_AVL, Rotations_LL_RR_LR_RL) {
  map<int, int> LL;
  LL.insert({30, 0});
  LL.insert({20, 0});
  LL.insert({10, 0});
  EXPECT_EQ(Collect(LL).front().first, 10);

  map<int, int> RR;
  RR.insert({10, 0});
  RR.insert({20, 0});
  RR.insert({30, 0});
  EXPECT_EQ(Collect(RR).back().first, 30);

  map<int, int> LR;
  LR.insert({30, 0});
  LR.insert({10, 0});
  LR.insert({20, 0});
  auto vLR = Collect(LR);
  EXPECT_EQ((std::vector<int>{vLR[0].first, vLR[1].first, vLR[2].first}),
            (std::vector<int>{10, 20, 30}));

  map<int, int> RL;
  RL.insert({10, 0});
  RL.insert({30, 0});
  RL.insert({20, 0});
  auto vRL = Collect(RL);
  EXPECT_EQ((std::vector<int>{vRL[0].first, vRL[1].first, vRL[2].first}),
            (std::vector<int>{10, 20, 30}));
}

template <class T>
static std::vector<T> ToStdVector(const s21_containers::list<T>& lst) {
  std::vector<T> out;
  for (auto it = lst.begin(); it != lst.end(); ++it) out.push_back(*it);
  return out;
}

TEST(ListInsertMany, Back_BasicOrderAndSize) {
  s21_containers::list<int> lst{1, 2, 3};
  lst.insert_many_back(4, 5, 6);
  auto got = ToStdVector(lst);
  std::vector<int> exp{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(got, exp);
  EXPECT_EQ(lst.size(), exp.size());
}

TEST(ListInsertMany, Front_BasicOrderAndSize) {
  s21_containers::list<int> lst{3, 4};
  lst.insert_many_front(0, 1, 2);
  auto got = ToStdVector(lst);
  std::vector<int> exp{0, 1, 2, 3, 4};
  EXPECT_EQ(got, exp);
  EXPECT_EQ(lst.size(), exp.size());
}

TEST(ListInsertMany, Front_OnEmptyList) {
  s21_containers::list<int> lst;
  lst.insert_many_front(10, 20);
  auto got = ToStdVector(lst);
  std::vector<int> exp{10, 20};
  EXPECT_EQ(got, exp);
  EXPECT_EQ(lst.size(), exp.size());
}

TEST(ListInsertMany, Back_OnEmptyList) {
  s21_containers::list<int> lst;
  lst.insert_many_back(7, 8, 9);
  auto got = ToStdVector(lst);
  std::vector<int> exp{7, 8, 9};
  EXPECT_EQ(got, exp);
  EXPECT_EQ(lst.size(), exp.size());
}

TEST(ListInsertMany, AtBegin_PosIsCBegin) {
  s21_containers::list<int> lst{10, 11};
  auto it_first = lst.insert_many(lst.cbegin(), -2, -1, 0);
  // возвращённый итератор должен указывать на первый вставленный элемент
  ASSERT_NE(it_first, lst.end());
  EXPECT_EQ(*it_first, -2);

  auto got = ToStdVector(lst);
  std::vector<int> exp{-2, -1, 0, 10, 11};
  EXPECT_EQ(got, exp);
}

TEST(ListInsertMany, InTheMiddle_AndAtEnd) {
  s21_containers::list<int> lst{1, 4, 5};
  // вставка в середину (перед 4)
  auto pos_mid = ++lst.begin();  // указывает на 4
  lst.insert_many(pos_mid, 2, 3);

  // вставка в конец: pos == end()
  lst.insert_many(lst.cend(), 6, 7);

  auto got = ToStdVector(lst);
  std::vector<int> exp{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(got, exp);
  EXPECT_EQ(lst.size(), exp.size());
}

TEST(ListInsertMany, EmptyParameterPack_NoChange) {
  s21_containers::list<int> lst{1, 2};
  std::size_t before = lst.size();
  // пустой пак аргументов — поведение: список не меняется, возвращается pos
  auto pos = ++lst.begin();  // указывает на 2
  auto it = lst.insert_many(pos /*, нет аргументов */);
  EXPECT_EQ(lst.size(), before);
  EXPECT_EQ(it, pos);
  auto got = ToStdVector(lst);
  std::vector<int> exp{1, 2};
  EXPECT_EQ(got, exp);
}

TEST(ListInsertMany, IteratorStability_AndOrder) {
  s21_containers::list<std::string> lst{"A", "D"};
  auto pos = ++lst.begin();  // перед "D"
  auto first = lst.insert_many(pos, std::string("B"), std::string("C"));
  ASSERT_NE(first, lst.end());
  EXPECT_EQ(*first, "B");
  auto got = ToStdVector(lst);
  std::vector<std::string> exp{"A", "B", "C", "D"};
  EXPECT_EQ(got, exp);
}

// MAP tests

TEST(MapInsertMany, BasicAndDuplicates) {
  s21_containers::map<int, std::string> m;
  using V = s21_containers::map<int, std::string>::value_type;

  auto res = m.insert_many(V{2, "two"}, V{1, "one"}, V{2, "TWO-dup"}
                           // дубликат ключа 2 — не должен вставиться
  );

  // Проверим результаты вставки (по порядку аргументов)
  ASSERT_EQ(res.size(), 3u);
  EXPECT_TRUE(res[0].second);  // key=2 вставился
  EXPECT_TRUE(res[1].second);  // key=1 вставился
  EXPECT_FALSE(res[2].second);  // дубликат key=2 — не вставился
  EXPECT_EQ(m.size(), 2u);

  // проверим порядок обхода итератором (in-order по ключам)
  std::vector<std::pair<int, std::string>> got;
  for (auto it = m.begin(); it != m.end(); ++it)
    got.emplace_back(it->first, it->second);
  std::vector<std::pair<int, std::string>> exp{{1, "one"}, {2, "two"}};
  EXPECT_EQ(got, exp);
}

TEST(MapInsertMany, EmptyParameterPack_NoChange) {
  s21_containers::map<int, int> m;
  auto res = m.insert_many(/* нет аргументов */);
  EXPECT_TRUE(res.empty());
  EXPECT_TRUE(m.empty());
}

TEST(MapInsertMany, LargeSequenceAndOrderInTree) {
  s21_containers::map<int, int> m;
  using V = s21_containers::map<int, int>::value_type;
  // Несортированная последовательность, чтобы «потрясти» балансировку
  auto res = m.insert_many(V{5, 50}, V{3, 30}, V{7, 70}, V{2, 20}, V{4, 40},
                           V{6, 60}, V{8, 80});
  ASSERT_EQ(res.size(), 7u);
  for (auto& p : res) EXPECT_TRUE(p.second);
  EXPECT_EQ(m.size(), 7u);

  // Проверка in-order
  std::vector<int> keys;
  for (auto it = m.begin(); it != m.end(); ++it) keys.push_back(it->first);
  std::vector<int> exp_keys{2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(keys, exp_keys);
}

TEST(MapInsertMany, IteratorValidityFromResult) {
  s21_containers::map<int, std::string> m;
  using V = s21_containers::map<int, std::string>::value_type;
  auto res = m.insert_many(V{10, "ten"}, V{5, "five"});
  ASSERT_EQ(res.size(), 2u);
  // Итераторы в result должны быть разыменуемыми
  EXPECT_EQ(res[0].first->first, 10);
  EXPECT_EQ(res[0].first->second, "ten");
  EXPECT_EQ(res[1].first->first, 5);
  EXPECT_EQ(res[1].first->second, "five");
}

// Краевой случай: много дубликатов — должен вставиться только первый
TEST(MapInsertMany, ManyDuplicates_OnlyFirstInserted) {
  s21_containers::map<int, int> m;
  using V = s21_containers::map<int, int>::value_type;
  auto res = m.insert_many(V{1, 11}, V{1, 22}, V{1, 33}, V{1, 44});
  ASSERT_EQ(res.size(), 4u);
  EXPECT_TRUE(res[0].second);
  EXPECT_FALSE(res[1].second);
  EXPECT_FALSE(res[2].second);
  EXPECT_FALSE(res[3].second);
  EXPECT_EQ(m.size(), 1u);
  EXPECT_EQ(m.at(1), 11);
}
