#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <new>
#include <stdexcept>
#include <utility>

namespace s21_containers {

template <class Key, class T, class Compare = std::less<Key>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using key_compare = Compare;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type kv;
    Node* left{nullptr};
    Node* right{nullptr};
    Node* parent{nullptr};
    int height{1};
    explicit Node(const value_type& v) : kv(v) {}
    explicit Node(value_type&& v) : kv(std::move(v)) {}
  };

  Node* root_{nullptr};
  size_type size_{0};
  key_compare comp_{};

  static int H(Node* n) { return n ? n->height : 0; }
  static void Upd(Node* n) {
    int hl = H(n->left), hr = H(n->right);
    n->height = 1 + (hl > hr ? hl : hr);
  }
  static int Bf(Node* n) { return H(n->left) - H(n->right); }

  Node* RotRight(Node* y) {
    Node* x = y->left;
    Node* t2 = x->right;
    x->right = y;
    y->left = t2;
    if (t2) t2->parent = y;
    x->parent = y->parent;
    y->parent = x;
    Upd(y);
    Upd(x);
    return x;
  }
  Node* RotLeft(Node* x) {
    Node* y = x->right;
    Node* t2 = y->left;
    y->left = x;
    x->right = t2;
    if (t2) t2->parent = x;
    y->parent = x->parent;
    x->parent = y;
    Upd(x);
    Upd(y);
    return y;
  }
  Node* Rebalance(Node* n) {
    Upd(n);
    int b = Bf(n);
    if (b > 1) {
      if (Bf(n->left) < 0) n->left = RotLeft(n->left);
      return RotRight(n);
    }
    if (b < -1) {
      if (Bf(n->right) > 0) n->right = RotRight(n->right);
      return RotLeft(n);
    }
    return n;
  }

  Node* InsertNode(Node* node, Node* parent, value_type&& kv, bool* inserted,
                   Node** out) {
    if (!node) {
      Node* n = new Node(std::move(kv));
      n->parent = parent;
      *inserted = true;
      *out = n;
      ++size_;
      return n;
    }
    if (comp_(kv.first, node->kv.first)) {
      node->left = InsertNode(node->left, node, std::move(kv), inserted, out);
    } else if (comp_(node->kv.first, kv.first)) {
      node->right = InsertNode(node->right, node, std::move(kv), inserted, out);
    } else {
      *inserted = false;
      *out = node;
      return node;
    }
    Node* r = Rebalance(node);
    return r;
  }

  static Node* Min(Node* n) {
    while (n && n->left) n = n->left;
    return n;
  }
  static Node* Next(Node* n) {
    if (!n) return nullptr;
    if (n->right) {
      n = n->right;
      while (n->left) n = n->left;
      return n;
    }
    Node* p = n->parent;
    while (p && p->right == n) {
      n = p;
      p = p->parent;
    }
    return p;
  }
  static Node* Prev(Node* n) {
    if (!n) return nullptr;
    if (n->left) {
      n = n->left;
      while (n->right) n = n->right;
      return n;
    }
    Node* p = n->parent;
    while (p && p->left == n) {
      n = p;
      p = p->parent;
    }
    return p;
  }

  Node* EraseNode(Node* node, const key_type& key, bool* erased) {
    if (!node) return nullptr;
    if (comp_(key, node->kv.first)) {
      node->left = EraseNode(node->left, key, erased);
      if (node->left) node->left->parent = node;
    } else if (comp_(node->kv.first, key)) {
      node->right = EraseNode(node->right, key, erased);
      if (node->right) node->right->parent = node;
    } else {
      *erased = true;
      if (!node->left || !node->right) {
        Node* child = node->left ? node->left : node->right;
        if (child) child->parent = node->parent;
        delete node;
        --size_;
        return child;
      } else {
        Node* s = Min(node->right);
        node->kv.~value_type();
        new (&node->kv) value_type(s->kv.first, s->kv.second);

        node->right = EraseNode(node->right, s->kv.first, erased);
        if (node->right) node->right->parent = node;
      }
    }
    return Rebalance(node);
  }

  static void Destroy(Node* n) {
    if (!n) return;
    Destroy(n->left);
    Destroy(n->right);
    delete n;
  }

  Node* FindNode(const key_type& key) const {
    Node* cur = root_;
    while (cur) {
      if (comp_(key, cur->kv.first))
        cur = cur->left;
      else if (comp_(cur->kv.first, key))
        cur = cur->right;
      else
        return cur;
    }
    return nullptr;
  }

 public:
  class iterator {
    friend class map;
    Node* cur_{nullptr};
    explicit iterator(Node* n) : cur_(n) {}

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<const Key, T>;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator() = default;
    reference operator*() const { return cur_->kv; }
    pointer operator->() const { return &cur_->kv; }
    iterator& operator++() {
      cur_ = Next(cur_);
      return *this;
    }
    iterator operator++(int) {
      iterator t(*this);
      ++(*this);
      return t;
    }
    iterator& operator--() {
      cur_ = Prev(cur_);
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
    friend class map;
    const Node* cur_{nullptr};
    explicit const_iterator(const Node* n) : cur_(n) {}

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<const Key, T>;
    using reference = const value_type&;
    using pointer = const value_type*;
    using iterator_category = std::bidirectional_iterator_tag;

    const_iterator() = default;
    const_iterator(const iterator& it) : cur_(it.cur_) {}
    reference operator*() const { return cur_->kv; }
    pointer operator->() const { return &cur_->kv; }
    const_iterator& operator++() {
      cur_ = Next(const_cast<Node*>(cur_));
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator t(*this);
      ++(*this);
      return t;
    }
    const_iterator& operator--() {
      cur_ = Prev(const_cast<Node*>(cur_));
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator t(*this);
      --(*this);
      return t;
    }
    bool operator==(const const_iterator& o) const { return cur_ == o.cur_; }
    bool operator!=(const const_iterator& o) const { return !(*this == o); }
  };

  map() = default;
  map(std::initializer_list<value_type> il) {
    for (auto& kv : il) insert(kv);
  }
  map(const map& other) : map() {
    for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
  }
  map(map&& other) noexcept
      : root_(other.root_), size_(other.size_), comp_(other.comp_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }
  map& operator=(map other) noexcept {
    swap(other);
    return *this;
  }
  ~map() { Destroy(root_); }

  iterator begin() noexcept { return iterator{Min(root_)}; }
  iterator end() noexcept { return iterator{nullptr}; }
  const_iterator begin() const noexcept { return const_iterator{Min(root_)}; }
  const_iterator end() const noexcept { return const_iterator{nullptr}; }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return static_cast<size_type>(-1) / sizeof(Node);
  }

  mapped_type& at(const key_type& key) {
    Node* n = FindNode(key);
    if (!n) throw std::out_of_range("s21::map::at: key not found");
    return n->kv.second;
  }
  const mapped_type& at(const key_type& key) const {
    const Node* n = FindNode(key);
    if (!n) throw std::out_of_range("s21::map::at: key not found");
    return n->kv.second;
  }
  mapped_type& operator[](const key_type& key) {
    Node* n = FindNode(key);
    if (!n) {
      auto [it, ok] = insert(value_type(key, mapped_type{}));
      (void)ok;
      n = it.cur_;
    }
    return n->kv.second;
  }

  void clear() noexcept {
    Destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    bool ins = false;
    Node* new_node = nullptr;
    root_ = InsertNode(root_, nullptr, value_type(value.first, value.second),
                       &ins, &new_node);
    if (root_) root_->parent = nullptr;
    return {iterator{new_node}, ins};
  }
  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    return insert(value_type(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    Node* n = FindNode(key);
    if (n) {
      n->kv.second = obj;
      return {iterator{n}, false};
    }
    return insert(value_type(key, obj));
  }

  // Part 3: insert_many
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(
      Args&&... args) {  // поменять на собственный вектор!!!
    std::vector<std::pair<iterator, bool>> res;
    res.reserve(sizeof...(Args));
    (void)std::initializer_list<int>{
        (res.push_back(this->insert(std::forward<Args>(args))), 0)...};
    return res;
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    bool erased = false;
    root_ = EraseNode(root_, pos.cur_->kv.first, &erased);
    if (root_) root_->parent = nullptr;
  }
  size_type erase(const key_type& key) {
    bool erased = false;
    root_ = EraseNode(root_, key, &erased);
    if (root_) root_->parent = nullptr;
    return erased ? 1u : 0u;
  }

  void swap(map& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  void merge(map& other) {
    for (auto it = other.begin(); it != other.end();) {
      const key_type k = it->first;
      if (!contains(k)) {
        insert(*it);
        auto cur = it++;
        other.erase(cur);
      } else {
        ++it;
      }
    }
  }

  bool contains(const key_type& key) const noexcept {
    return FindNode(key) != nullptr;
  }
};

}  // namespace s21_containers

#endif