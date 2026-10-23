#ifndef MULTISET_H
#define MULTISET_H

#include "s21_set.hpp"

namespace s21_containers {
template <typename T>
class multiset : public set<T> {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = typename set<T>::SetIterator;
  using const_iterator = typename set<T>::SetConstIterator;

 public:
  multiset() : set<T>() {}

  multiset(std::initializer_list<value_type> const& items) : set<T>() {
    for (const auto& item : items) {
      insert(item);
    }
  }

  multiset(const multiset& other) : set<T>(other) {}

  multiset(multiset&& other) noexcept : set<T>(std::move(other)) {}

  std::pair<iterator, bool> insert(const value_type& value) override {
    auto newNode = this->insertWithoutCheck(value);
    return std::make_pair(iterator(newNode, this->root), true);
  }

  bool contains(const T& key) const override { return count(key) > 0; }

  size_type count(const T& key) const {
    size_type cnt = 0;
    for (auto it = this->begin(); it != this->end(); ++it) {
      if (*it == key) {
        cnt++;
      } else if (cnt > 0) {
        break;
      }
    }
    return cnt;
  }

  iterator lower_bound(const T& key) {
    for (auto it = this->begin(); it != this->end(); ++it) {
      if (*it >= key) {
        return it;
      }
    }
    return this->end();
  }

  iterator upper_bound(const T& key) {
    for (auto it = this->begin(); it != this->end(); ++it) {
      if (*it > key) {
        return it;
      }
    }
    return this->end();
  }

  std::pair<iterator, iterator> equal_range(const T& key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  size_type erase(const T& key) {
    size_type removed_count = 0;
    auto it = this->begin();

    while (it != this->end()) {
      if (*it == key) {
        auto to_erase = it;
        ++it;
        set<T>::erase(to_erase);
        ++removed_count;
      } else {
        ++it;
      }
    }

    return removed_count;
  }

  using set<T>::begin;
  using set<T>::end;
  using set<T>::find;
  using set<T>::clear;
  using set<T>::size;
  using set<T>::empty;
  using set<T>::swap;
  using set<T>::print;
  using set<T>::printStructure;
};
};  // namespace s21_containers

#endif  // MULTISET_H