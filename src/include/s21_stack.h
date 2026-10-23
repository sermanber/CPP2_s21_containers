#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21_containers {

template <typename T>

class stack {
 public:
  stack() noexcept;
  stack(std::initializer_list<T> init);
  stack(const stack& other);
  stack(stack&& other) noexcept;
  ~stack();

  stack& operator=(const stack& other);
  stack& operator=(stack&& other) noexcept;

  void push(const T& value);
  void pop();
  T& top();
  const T& top() const;
  bool empty() const noexcept;
  size_t size() const noexcept;
  void clear() noexcept;
  void swap(stack& other) noexcept;
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value, Node* next_node = nullptr)
        : data(value), next(next_node) {}
  };

  Node* topNode_;
  size_t size_;

  void copyFrom(const stack& other);
  void moveFrom(stack&& other) noexcept;
  void deleteAllNodes();
};

// Реализация шаблонов

// Конструкторы

template <typename T>
stack<T>::stack() noexcept : topNode_(nullptr), size_(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<T> init) : stack() {
  for (auto it = init.begin(); it != init.end(); ++it) {
    push(*it);
  }
}

template <typename T>
stack<T>::stack(const stack& other) : stack() {
  copyFrom(other);
}

template <typename T>
stack<T>::stack(stack&& other) noexcept : stack() {
  moveFrom(std::move(other));
}

template <typename T>
stack<T>::~stack() {
  deleteAllNodes();
}

// Вспомогательные функции

template <typename T>
void stack<T>::deleteAllNodes() {
  while (topNode_) {
    Node* tmp = topNode_;
    topNode_ = topNode_->next;
    delete tmp;
  }
  size_ = 0;
}

template <typename T>
void stack<T>::copyFrom(const stack& other) {
  if (other.empty()) return;

  // Заменяем VLA на динамический массив
  Node** nodes = new Node*[other.size_];
  size_t idx = 0;

  Node* curr_other = other.topNode_;
  while (curr_other) {
    nodes[idx++] = curr_other;
    curr_other = curr_other->next;
  }

  for (int i = idx - 1; i >= 0; --i) {
    push(nodes[i]->data);
  }

  delete[] nodes;  // Освобождаем память
}

template <typename T>
void stack<T>::moveFrom(stack&& other) noexcept {
  topNode_ = other.topNode_;
  size_ = other.size_;
  other.topNode_ = nullptr;
  other.size_ = 0;
}

// Присваивания

template <typename T>
stack<T>& stack<T>::operator=(const stack& other) {
  if (this != &other) {
    deleteAllNodes();
    copyFrom(other);
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& other) noexcept {
  if (this != &other) {
    deleteAllNodes();
    moveFrom(std::move(other));
  }
  return *this;
}

// Основные методы

template <typename T>
void stack<T>::push(const T& value) {
  Node* newNode = new Node(value, topNode_);
  topNode_ = newNode;
  ++size_;
}

template <typename T>
void stack<T>::pop() {
  if (empty()) throw std::out_of_range("Stack is empty");
  Node* tmp = topNode_;
  topNode_ = topNode_->next;
  delete tmp;
  --size_;
}

template <typename T>
T& stack<T>::top() {
  if (empty()) throw std::out_of_range("Stack is empty");
  return topNode_->data;
}

template <typename T>
const T& stack<T>::top() const {
  if (empty()) throw std::out_of_range("Stack is empty");
  return topNode_->data;
}

template <typename T>
bool stack<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
size_t stack<T>::size() const noexcept {
  return size_;
}

template <typename T>
void stack<T>::clear() noexcept {
  deleteAllNodes();
}

template <typename T>
void stack<T>::swap(stack& other) noexcept {
  std::swap(topNode_, other.topNode_);
  std::swap(size_, other.size_);
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
};

}  // namespace s21_containers

#endif