#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21_containers {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type value{};
    Node* prev{nullptr};
    Node* next{nullptr};
    Node() = default;
    explicit Node(const value_type& v) : value(v) {}
    explicit Node(value_type&& v) : value(std::move(v)) {}
  };

  Node* sentry_{nullptr};
  size_type size_{0};

  void InitSentry() {
    sentry_ = new Node();
    sentry_->next = sentry_;
    sentry_->prev = sentry_;
  }
  void LinkBetween(Node* left, Node* node, Node* right) {
    left->next = node;
    node->prev = left;
    node->next = right;
    right->prev = node;
  }
  void Unlink(Node* n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }
  // Переместить фронтовой узел из src в конец this
  void TakeFrontFrom(list& src) {
    if (src.empty()) return;
    Node* n = src.sentry_->next;
    src.Unlink(n);
    --src.size_;
    // вставляем n перед sentry_ (в конец this)
    LinkBetween(sentry_->prev, n, sentry_);
    ++size_;
  }

  // Слить отсортированный 'from' в отсортированный 'to' (исп-ся в sort)
  static void MergeInto(list& to, list& from) {
    auto it = to.begin();
    auto oit = from.begin();
    while (oit != from.end()) {
      while (it != to.end() && *it <= *oit) ++it;
      Node* on = oit.cur_;
      ++oit;
      from.Unlink(on);
      --from.size_;
      to.LinkBetween(it.cur_->prev, on, it.cur_);
      ++to.size_;
    }
  }

 public:
  class iterator {
    friend class list;
    Node* cur_{nullptr};
    explicit iterator(Node* n) : cur_(n) {}

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator() = default;
    reference operator*() const { return cur_->value; }
    pointer operator->() const { return &cur_->value; }
    iterator& operator++() {
      cur_ = cur_->next;
      return *this;
    }
    iterator operator++(int) {
      iterator t(*this);
      ++(*this);
      return t;
    }
    iterator& operator--() {
      cur_ = cur_->prev;
      return *this;
    }
    iterator operator--(int) {
      iterator t(*this);
      --(*this);
      return t;
    }
    bool operator==(const iterator& o) const { return cur_ == o.cur_; }
    bool operator!=(const iterator& o) const { return !(*this == o); }
  };

  class const_iterator {
    friend class list;
    const Node* cur_{nullptr};
    explicit const_iterator(const Node* n) : cur_(n) {}

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = const T&;
    using pointer = const T*;
    using iterator_category = std::bidirectional_iterator_tag;

    const_iterator() = default;
    const_iterator(const iterator& it) : cur_(it.cur_) {}
    reference operator*() const { return cur_->value; }
    pointer operator->() const { return &cur_->value; }
    const_iterator& operator++() {
      cur_ = cur_->next;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator t = *this;
      ++(*this);
      return t;
    }
    const_iterator& operator--() {
      cur_ = cur_->prev;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator t = *this;
      --(*this);
      return t;
    }
    bool operator==(const const_iterator& o) const { return cur_ == o.cur_; }
    bool operator!=(const const_iterator& o) const { return !(*this == o); }
  };

  list() { InitSentry(); }

  explicit list(size_type n) : list() {
    while (n--) push_back(value_type{});
  }

  list(std::initializer_list<value_type> il) : list() {
    for (const auto& v : il) push_back(v);
  }

  list(const list& other) : list() {
    for (const auto& v : other) push_back(v);
  }

  list(list&& other) noexcept : sentry_(other.sentry_), size_(other.size_) {
    other.InitSentry();
    other.size_ = 0;
  }

  list& operator=(list other) noexcept {
    swap(other);
    return *this;
  }

  ~list() {
    clear();
    delete sentry_;
  }

  reference front() {
    if (empty()) throw std::out_of_range("list::front on empty");
    return sentry_->next->value;
  }
  reference back() {
    if (empty()) throw std::out_of_range("list::back on empty");
    return sentry_->prev->value;
  }
  const_reference front() const { return const_cast<list*>(this)->front(); }
  const_reference back() const { return const_cast<list*>(this)->back(); }

  iterator begin() noexcept { return iterator{sentry_->next}; }
  iterator end() noexcept { return iterator{sentry_}; }
  const_iterator begin() const noexcept {
    return const_iterator{sentry_->next};
  }
  const_iterator end() const noexcept { return const_iterator{sentry_}; }
  const_iterator cbegin() const noexcept { return begin(); }
  const_iterator cend() const noexcept { return end(); }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  void clear() noexcept {
    Node* n = sentry_->next;
    while (n != sentry_) {
      Node* next = n->next;
      delete n;
      n = next;
    }
    sentry_->next = sentry_->prev = sentry_;
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    Node* node = new Node(value);
    LinkBetween(pos.cur_->prev, node, pos.cur_);
    ++size_;
    return iterator{node};
  }
  iterator insert(iterator pos, value_type&& value) {
    Node* node = new Node(std::move(value));
    LinkBetween(pos.cur_->prev, node, pos.cur_);
    ++size_;
    return iterator{node};
  }

  iterator erase(iterator pos) {
    if (pos == end()) return pos;
    Node* n = pos.cur_;
    iterator next{n->next};
    Unlink(n);
    delete n;
    --size_;
    return next;
  }

  void push_back(const_reference v) { insert(end(), v); }
  void push_back(value_type&& v) { insert(end(), std::move(v)); }
  void pop_back() {
    if (!empty()) erase(--end());
  }

  void push_front(const_reference v) { insert(begin(), v); }
  void push_front(value_type&& v) { insert(begin(), std::move(v)); }
  void pop_front() {
    if (!empty()) erase(begin());
  }

  //  Part 3: insert_many
  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator stable_pos{const_cast<Node*>(pos.cur_)};
    iterator first_it = stable_pos;

    (void)std::initializer_list<int>{(
        [&]() {
          iterator it = insert(stable_pos, std::forward<Args>(args));
          if (first_it == stable_pos) {
            first_it = it;
          }
        }(),
        0)...};

    return first_it;
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    (void)std::initializer_list<int>{
        (insert(end(), std::forward<Args>(args)), 0)...};
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    iterator stable_pos = begin();
    (void)std::initializer_list<int>{
        (insert(stable_pos, std::forward<Args>(args)), 0)...};
  }

  void swap(list& other) noexcept {
    std::swap(sentry_, other.sentry_);
    std::swap(size_, other.size_);
  }

  // merge: предполагается, что оба списка уже отсортированы по operator<
  void merge(list& other) {
    if (this == &other || other.empty()) return;
    auto it = begin();
    auto oit = other.begin();
    while (oit != other.end()) {
      // найдём место, куда переносить узел
      while (it != end() && *it <= *oit) ++it;
      // вырезаем узел из other и вставляем перед it
      Node* on = oit.cur_;
      ++oit;
      other.Unlink(on);
      --other.size_;
      LinkBetween(it.cur_->prev, on, it.cur_);
      ++size_;
    }
  }

  // splice: переносит ВСЕ элементы other перед pos
  void splice(const_iterator pos, list& other) {
    if (this == &other || other.empty()) return;
    Node* first = other.sentry_->next;
    Node* last = other.sentry_->prev;
    // вырезать интервал [first..last] из other
    other.sentry_->next = other.sentry_;
    other.sentry_->prev = other.sentry_;
    // вставить перед pos
    Node* left = const_cast<Node*>(pos.cur_)->prev;
    left->next = first;
    first->prev = left;
    last->next = const_cast<Node*>(pos.cur_);
    const_cast<Node*>(pos.cur_)->prev = last;
    size_ += other.size_;
    other.size_ = 0;
  }

  void reverse() {
    if (size_ < 2) return;
    Node* n = sentry_;
    do {
      std::swap(n->next, n->prev);
      n = n->prev;  // потому что поменяли местами
    } while (n != sentry_);
  }

  // удаляет подряд идущие дубликаты (равные соседние элементы)
  void unique() {
    if (size_ < 2) return;
    auto it = begin();
    auto next = it;
    ++next;
    while (next != end()) {
      if (*it == *next) {
        next = erase(next);
      } else {
        ++it;
        ++next;
      }
    }
  }

  void sort() {
    if (size_ < 2) return;

    list buckets[64];
    size_type fill = 0;

    while (!empty()) {
      list carry;
      carry.TakeFrontFrom(*this);  // <-- берём ровно один узел

      size_type i = 0;
      while (i < fill && !buckets[i].empty()) {
        // buckets[i] и carry отсортированы — сольём их в carry
        MergeInto(carry, buckets[i]);
        buckets[i].swap(carry);
        ++i;
      }
      buckets[i].swap(carry);
      if (i == fill) ++fill;
    }

    for (size_type i = 1; i < fill; ++i) {
      MergeInto(buckets[i], buckets[i - 1]);
      buckets[i - 1].clear();
    }
    swap(buckets[fill - 1]);
  }

  template <class U = T>
  static bool LessOrEq(const U& a, const U& b) {
    return a <= b;
  }
};

}  // namespace s21_containers
#endif