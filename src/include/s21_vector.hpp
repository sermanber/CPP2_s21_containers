#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>

namespace s21_containers {
template <typename T>
class vector {
 private:
  T* data_;
  size_t size_;
  size_t capacity_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;
  //--------------Interface--------------
  vector() : data_{nullptr}, size_{0}, capacity_{0} {}

  vector(size_t n) : data_{nullptr}, size_{0}, capacity_{0} {
    if (n > 0) {
      data_ = new T[n];
      size_ = n;
      capacity_ = n;

      for (size_t i = 0; i < n; i++) {
        data_[i] = T();
      }
    }
  }

  vector(const vector<T>& v) : data_{nullptr}, size_{0}, capacity_{0} {
    if (v.size_ != 0) {
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = new T[v.capacity_];
      for (size_t i = 0; i < v.size_; i++) {
        data_[i] = v.data_[i];
      }
    }
  }

  vector(vector<T>&& temp)
      : data_{temp.data_}, size_{temp.size_}, capacity_{temp.capacity_} {
    temp.data_ = nullptr;
    temp.size_ = 0;
    temp.capacity_ = 0;
  }

  vector(std::initializer_list<value_type> const& items)
      : data_(nullptr), size_(0), capacity_(0) {
    reserve(items.size());
    for (const auto& item : items) {
      push_back(item);
    }
  }

  vector<T>& operator=(vector<T>& v) {
    if (this != &v) {
      delete[] data_;

      if (v.size_ > 0) {
        data_ = new T[v.capacity_];
        size_ = v.size_;
        capacity_ = v.capacity_;
        for (size_t i = 0; i < size_; i++) {
          data_[i] = v.data_[i];
        }
      } else {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
      }
    }
    return *this;
  }
  //--------------operator and func--------------
  T& operator[](size_t ind) { return data_[ind]; }

  T& at(size_t ind) {
    if (ind >= size_) throw std::out_of_range("Index out of range");
    return data_[ind];
  }

  T& front() { return data_[0]; }
  T& back() { return data_[size_ - 1]; }

  T* data() { return data_; }
  T* begin() { return data_; }
  T* end() { return data_ + size_; }

  bool empty() { return (size_ == 0); }
  size_t size() { return size_; }
  size_t capacity() { return capacity_; }

  void reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
      T* new_data = new T[new_capacity];
      for (size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = new_capacity;
    }
  }

  void push_back(const T& value) {
    if (size_ == capacity_) {
      (capacity_ == 0) ? reserve(1) : reserve(capacity_ * 2);
    }
    data_[size_] = value;
    size_++;
  }
  void pop_back() {
    if (size_ > 0) {
      size_--;
    }
  }

  iterator insert(iterator pos, const_reference value) {
    size_t ind = pos - begin();
    if (ind > size_) {
      throw std::out_of_range("Index out of range");
    }
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    for (size_t i = size_; i > ind; i--) {
      data_[i] = data_[i - 1];
    }
    data_[ind] = value;
    size_++;
    return begin() + ind;
  }

  void erase(iterator pos) {
    size_t ind = pos - begin();
    if (ind >= size_) throw std::out_of_range("Index out of range");

    for (size_t i = ind; i < size_ - 1; i++) {
      data_[i] = data_[i + 1];
    }
    size_--;
  }

  void swap(vector<T>& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      T* new_data = new T[size_];
      for (size_t i = 0; i < size_; i++) {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
    }
  }

  size_t max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(T);
  }

  //--------------destr and some const method--------------

  void clear() { size_ = 0; }

  ~vector() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  const T& front() const { return data_[0]; }
  const T& back() const { return data_[size_ - 1]; }

  const T* data() const { return data_; }

  const T* begin() const { return data_; }
  const T* end() const { return data_ + size_; }

  const T& operator[](size_t ind) const { return data_[ind]; }

  const T& at(size_t ind) const {
    if (ind >= size_) throw std::out_of_range("Index out of range");
    return data_[ind];
  }

  const_iterator cbegin() const { return data_; }
  const_iterator cend() const { return data_ + size_; }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    size_t ind = pos - begin();
    if (ind > size_) {
      throw std::out_of_range("Index out of range");
    }

    size_t count = sizeof...(Args);
    if (size_ + count > capacity_) {
      reserve(capacity_ == 0 ? std::max(count, size_t(1))
                             : std::max(capacity_ * 2, size_ + count));
    }

    for (size_t i = size_; i > ind; --i) {
      data_[i + count - 1] = std::move(data_[i - 1]);
    }

    size_t current = ind;
    T new_elements[] = {std::forward<Args>(args)...};
    for (size_t i = 0; i < count; ++i) {
      data_[current++] = std::move(new_elements[i]);
    }

    size_ += count;
    return begin() + ind;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(end(), std::forward<Args>(args)...);
  }
};

};  // namespace s21_containers

#endif  // S21_VECTOR_H