#ifndef S21_ARRAY_TPP_
#define S21_ARRAY_TPP_

namespace s21_containers {

// Реализации для основного шаблона (N > 0)

template <typename T, std::size_t N>
array<T, N>::array() {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) throw std::length_error("Too many elements in items");
  std::copy(items.begin(), items.end(), data_);
  if (items.size() < N) std::fill(data_ + items.size(), data_ + N, T{});
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N> &other) {
  std::copy(other.data_, other.data_ + N, data_);
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N> &&other) noexcept {
  std::move(other.data_, other.data_ + N, data_);
  std::fill(other.data_, other.data_ + N, T{});
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array &other) {
  if (this != &other) std::copy(other.data_, other.data_ + N, data_);
  return *this;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&other) noexcept {
  if (this != &other) std::move(other.data_, other.data_ + N, data_);
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) throw std::out_of_range("Pos out of range");
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) throw std::out_of_range("Pos out of range");
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return data_ + N;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept {
  return data_ + N;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return N == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(data_, data_ + N, value);
}

template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N> &other) noexcept {
  std::swap_ranges(data_, data_ + N, other.data_);
}

}  // namespace s21_containers

#endif  // S21_ARRAY_TPP_
