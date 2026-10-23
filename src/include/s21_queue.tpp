#ifndef S21_QUEUE_TPP_
#define S21_QUEUE_TPP_

namespace s21_containers {
template <typename T>
queue<T>::queue() {}
template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); i++) {
    push(*i);
  }
}
template <typename T>
queue<T>::queue(const queue &other) {
  Node *cur = other.head;
  while (cur) {
    push(cur->data);
    cur = cur->prev;
  }
}
template <typename T>
queue<T>::queue(queue &&other) noexcept {
  head = other.head;
  tail = other.tail;
  size_ = other.size_;
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
}
template <typename T>
queue<T>::~queue() {
  while (head != nullptr) {
    pop();
  }
}
template <typename T>
typename queue<T>::queue &queue<T>::operator=(const queue &other) {
  if (this != &other) {
    while (head != nullptr) {
      pop();
    }
    Node *cur = other.head;
    while (cur) {
      push(cur->data);
      cur = cur->prev;
    }
  }
  return *this;
}
template <typename T>
typename queue<T>::queue &queue<T>::operator=(queue &&other) noexcept {
  if (this != &other) {
    while (head != nullptr) {
      pop();
    }
    head = other.head;
    tail = other.tail;
    size_ = other.size_;
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }

  return *this;
}
template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (empty()) throw std::out_of_range("Queue is empty");
  return head->data;
}
template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (empty()) throw std::out_of_range("Queue is empty");
  return tail->data;
}
template <typename T>
bool queue<T>::empty() const noexcept {
  return size_ == 0;
}
template <typename T>
typename queue<T>::size_type queue<T>::size() const noexcept {
  return size_;
}
template <typename T>
void queue<T>::push(const_reference value) {
  Node *new_Node = new Node(value, tail);
  if (head == nullptr) {
    head = new_Node;
    tail = head;
  } else {
    tail->prev = new_Node;
    tail = new_Node;
  }
  size_++;
}
template <typename T>
void queue<T>::pop() {
  if (empty()) throw std::out_of_range("Cannot pop from empty queue");
  Node *delNode = head;
  head = delNode->prev;
  if (head != nullptr) {
    head->next = nullptr;
  } else {
    tail = nullptr;
  }
  delete delNode;
  size_--;
}
template <typename T>
void queue<T>::swap(queue &other) noexcept {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size_, other.size_);
}
template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  // for (const auto& arg : {args...}){
  //     push(arg);
  // }
  (push(std::forward<Args>(args)), ...);
}
}  // namespace s21_containers

#endif