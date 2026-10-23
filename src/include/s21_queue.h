#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <algorithm>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <string>

namespace s21_containers {

template <typename T>
class queue {
 public:
  // Основные типы
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Констуркторы(деструкторы)
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &other);
  queue(queue &&other) noexcept;
  ~queue();

  // Присваивание копированием/перемещением
  queue &operator=(const queue &other);
  queue &operator=(queue &&other) noexcept;

  // Доступ к элементам
  const_reference front() const;
  const_reference back() const;

  // Ёмкость
  bool empty() const noexcept;
  size_type size() const noexcept;

  // Модификаторы
  void push(const_reference value);
  void pop();
  void swap(queue &other) noexcept;

  // Доп. модификаатор
  template <typename... Args>
  void insert_many_back(Args &&...args);

  //      tail                           head
  //      Node 1 ------> Node 2 -------> Node 3
  // (prev=nullptr)     next ->3      (next=nullptr)
  //                    prev <-1
 private:
  struct Node {
    value_type data{};
    Node *next = nullptr;
    Node *prev = nullptr;
    Node(const value_type &val, Node *nxt = nullptr, Node *prv = nullptr)
        : data(val), next(nxt), prev(prv) {}
  };

  Node *head = nullptr;
  Node *tail = nullptr;
  size_type size_ = 0;
};

}  // namespace s21_containers

#include "./s21_queue.tpp"

#endif
