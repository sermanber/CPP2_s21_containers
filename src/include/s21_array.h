#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <string>

namespace s21_containers {

// Основной шаблон класса array
template <typename T, std::size_t N>
class array {
 public:
  // Основные типы
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Конструкторы(деструкторы)
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other) noexcept;
  ~array() = default;

  // Присваивание копированием/перемещением
  array &operator=(const array &other);
  array &operator=(array &&other) noexcept;

  // Доступ к элементам
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;
  const_iterator data() const noexcept;

  // Итераторы
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  // Ёмкость
  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const;

  // Модификаторы
  void fill(const_reference value);
  void swap(array &other) noexcept;

 private:
  value_type data_[N]{};
};

// Специализация для массива нулевого размера
template <typename T>
class array<T, 0> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() = default;
  array(std::initializer_list<value_type> const &items) {
    if (items.size() > 0) throw std::length_error("Too many elements in items");
  }
  array(const array &other) = default;
  array(array &&other) noexcept = default;
  ~array() = default;

  array &operator=(const array &other) = default;
  array &operator=(array &&other) noexcept = default;

  reference at(size_type pos) {
    throw std::out_of_range("array: index out of range");
  }

  const_reference at(size_type pos) const {
    throw std::out_of_range("array: index out of range");
  }

  reference operator[](size_type pos) {
    throw std::out_of_range("array: index out of range");
  }

  const_reference operator[](size_type pos) const {
    throw std::out_of_range("array: index out of range");
  }

  const_reference front() const {
    throw std::out_of_range("array: index out of range");
  }

  const_reference back() const {
    throw std::out_of_range("array: index out of range");
  }

  iterator data() noexcept { return nullptr; }
  const_iterator data() const noexcept { return nullptr; }

  iterator begin() noexcept { return nullptr; }
  const_iterator begin() const noexcept { return nullptr; }
  const_iterator cbegin() const noexcept { return nullptr; }
  iterator end() noexcept { return nullptr; }
  const_iterator end() const noexcept { return nullptr; }
  const_iterator cend() const noexcept { return nullptr; }

  bool empty() const noexcept { return true; }
  size_type size() const { return 0; }
  size_type max_size() const { return 0; }

  void fill(const_reference value) {}
  void swap(array &other) noexcept {}
};

}  // namespace s21_containers

#include "s21_array.tpp"

#endif  // S21_ARRAY_H_
