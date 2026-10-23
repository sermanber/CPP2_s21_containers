#ifndef SET_H
#define SET_H

#include <iostream>
#include <limits>
#include <utility>

namespace s21_containers {
enum COLOR { RED, BLACK };

template <typename T>
class BST_RB_Noode {
  template <typename U>
  friend class set;
  template <typename U>
  friend class multiset;

 protected:
  T data;
  BST_RB_Noode<T>* left;
  BST_RB_Noode<T>* right;
  BST_RB_Noode<T>* parent;
  COLOR color;

 public:
  BST_RB_Noode(const T& v, COLOR c = BLACK, BST_RB_Noode<T>* p = nullptr)
      : data{v}, left{nullptr}, right{nullptr}, parent{p}, color{c} {}
  ~BST_RB_Noode() {}
};

template <typename T>
class set {
  template <typename U>
  friend class multiset;

 public:
  // typedef ТЗ
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  class SetIterator;
  class SetConstIterator;

 protected:
  BST_RB_Noode<T>* root;
  size_type size_ = 0;
  //--------------Min/Max/Key--------------
  static BST_RB_Noode<T>* findMin(BST_RB_Noode<T>* node) {
    if (node == nullptr) return nullptr;
    while (node->left) node = node->left;
    return node;
  }

  static BST_RB_Noode<T>* findMax(BST_RB_Noode<T>* node) {
    if (node == nullptr) return nullptr;
    while (node->right) node = node->right;
    return node;
  }

  BST_RB_Noode<T>* findNode(BST_RB_Noode<T>* node, const T& key) const {
    while (node) {
      if (key == node->data) return node;
      node = (key < node->data) ? node->left : node->right;
    }
    return nullptr;
  }
  //--------------findSuccessor/findPredcessor--------------
  static BST_RB_Noode<T>* findSuccessor(BST_RB_Noode<T>* node) {
    if (!node) return nullptr;
    if (node->right != nullptr) {
      return findMin(node->right);
    } else {
      BST_RB_Noode<T>* current = node;
      BST_RB_Noode<T>* parent = node->parent;
      while (parent != nullptr && current == parent->right) {
        current = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }

  static BST_RB_Noode<T>* findPredecessor(BST_RB_Noode<T>* node) {
    if (!node) return nullptr;
    if (node->left != nullptr) {
      return findMax(node->left);
    } else {
      BST_RB_Noode<T>* current = node;
      BST_RB_Noode<T>* parent = node->parent;
      while (parent != nullptr && current == parent->left) {
        current = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }

  //--------------fixCases/getters and some helpers--------------
  void fixLeftCases(BST_RB_Noode<T>* newNode, BST_RB_Noode<T>* grandparent,
                    BST_RB_Noode<T>* uncle) {
    if (uncle != nullptr && uncle->color == RED) {  // case 1, color correct
      newNode->parent->color = BLACK;
      uncle->color = BLACK;
      grandparent->color = RED;
      fixInsertion(grandparent);
    } else {
      if (newNode == newNode->parent->left) {  // case 2, uncle null or zigzag
        newNode = newNode->parent;
        RotationLeft(newNode);
      }
      // case 3, line
      newNode->parent->color = BLACK;
      grandparent->color = RED;
      RotationRight(grandparent);
    }
  }

  void fixRightCases(BST_RB_Noode<T>* newNode, BST_RB_Noode<T>* grandparent,
                     BST_RB_Noode<T>* uncle) {
    if (uncle != nullptr && uncle->color == RED) {  // case 1, color correct
      newNode->parent->color = BLACK;
      uncle->color = BLACK;
      grandparent->color = RED;
      fixInsertion(grandparent);
    } else {
      if (newNode == newNode->parent->right) {  // case 2, uncle null or zigzag
        newNode = newNode->parent;
        RotationRight(newNode);
      }
      // case 3, line
      newNode->parent->color = BLACK;
      grandparent->color = RED;
      RotationLeft(grandparent);
    }
  }

 protected:
  // for multiset
  BST_RB_Noode<T>* insertWithoutCheck(const value_type& v) {
    if (root == nullptr) {
      root = new BST_RB_Noode<T>(v, BLACK);
      size_ = 1;
      return root;
    }

    BST_RB_Noode<T>* current = root;
    BST_RB_Noode<T>* parent = nullptr;

    while (current != nullptr) {
      parent = current;
      if (v < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    BST_RB_Noode<T>* newNode = new BST_RB_Noode<T>(v, RED, parent);

    if (v < parent->data) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    fixInsertion(newNode);
    size_++;

    return newNode;
  }

  void RotationLeft(BST_RB_Noode<T>* x) {
    BST_RB_Noode<T>* y = x->right;
    if (y == nullptr) return;

    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
  }

  void RotationRight(BST_RB_Noode<T>* x) {
    BST_RB_Noode<T>* y = x->left;
    if (y == nullptr) return;

    x->left = y->right;
    if (y->right != nullptr) {
      y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
  }

  BST_RB_Noode<T>* getUncle(BST_RB_Noode<T>* node) {
    BST_RB_Noode<T>* grandparent = getGrandparent(node);
    if (grandparent == nullptr) return nullptr;

    return (node->parent == grandparent->left) ? grandparent->right
                                               : grandparent->left;
  }

  BST_RB_Noode<T>* getGrandparent(BST_RB_Noode<T>* node) {
    if (node->parent == nullptr || node == nullptr) return nullptr;
    return node->parent->parent;
  }

  BST_RB_Noode<T>* copyTree(BST_RB_Noode<T>* original,
                            BST_RB_Noode<T>* parent) {
    if (original == nullptr) {
      return nullptr;
    }

    BST_RB_Noode<T>* newNode =
        new BST_RB_Noode<T>(original->data, original->color, parent);
    newNode->left = copyTree(original->left, newNode);
    newNode->right = copyTree(original->right, newNode);
    return newNode;
  }

  void clearHelper(BST_RB_Noode<T>* node) {
    if (node == nullptr) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
  }

  void inOrderHelper(BST_RB_Noode<T>* node) const {
    if (node == nullptr) return;
    inOrderHelper(node->left);
    std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
    inOrderHelper(node->right);
  }

  void printStructureHelper(BST_RB_Noode<T>* node, int depth) const {
    if (node == nullptr) return;

    printStructureHelper(node->right, depth + 1);

    for (int i = 0; i < depth; i++) {
      std::cout << "   ";
    }
    std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ")";
    if (node->parent) {
      std::cout << " parent:" << node->parent->data;
    } else {
      std::cout << "[root]";
    }
    std::cout << std::endl;

    printStructureHelper(node->left, depth + 1);
  }

  void fixInsertion(BST_RB_Noode<T>* newNode) {
    if (newNode->parent == nullptr) {  // it is root
      newNode->color = BLACK;
      root = newNode;
      return;
    }

    if (newNode->parent->color == BLACK) {
      return;
    }

    BST_RB_Noode<T>* uncle = getUncle(newNode);
    BST_RB_Noode<T>* grandparent = getGrandparent(newNode);

    if (grandparent != nullptr) {
      if (newNode->parent == grandparent->left) {  // left children
        fixLeftCases(newNode, grandparent, uncle);
      } else {
        fixRightCases(newNode, grandparent, uncle);  // right children
      }
    }
    root->color = BLACK;
  }

  void margeHelper(BST_RB_Noode<T>* node, set<T>& buff) {
    if (node == nullptr) return;
    if (!search(node->data)) {
      buff.insert(node->data);
    }
    margeHelper(node->left, buff);
    margeHelper(node->right, buff);
  }

  void margeBuff(set<T>& buff) { mergeBuffHelper(buff.root); }

  void mergeBuffHelper(BST_RB_Noode<T>* nood) {
    if (nood == nullptr) return;
    insert(nood->data);
    mergeBuffHelper(nood->left);
    mergeBuffHelper(nood->right);
  }

  //--------------delete--------------
  void transplant(BST_RB_Noode<T>* u, BST_RB_Noode<T>* v) {
    if (u == nullptr) return;

    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }

    if (v != nullptr) {
      v->parent = u->parent;
    }
  }

  void deleteNode(BST_RB_Noode<T>* z) {
    if (z == nullptr) return;

    BST_RB_Noode<T>* y = z;
    BST_RB_Noode<T>* x = nullptr;
    COLOR y_original_color = y->color;

    if (z->left == nullptr) {
      // Case 1: no left children
      x = z->right;
      transplant(z, z->right);
    } else if (z->right == nullptr) {
      // Case 2: no right children
      x = z->left;
      transplant(z, z->left);
    } else {
      // Case 3: two children
      y = findMin(z->right);
      if (y == nullptr) {
        return;
      }
      y_original_color = y->color;
      x = y->right;

      if (y->parent == z) {
        if (x != nullptr) {
          x->parent = y;
        }
      } else {
        transplant(y, y->right);
        y->right = z->right;
        if (y->right != nullptr) {
          y->right->parent = y;
        }
      }

      transplant(z, y);
      y->left = z->left;
      if (y->left != nullptr) {
        y->left->parent = y;
      }
      y->color = z->color;
    }

    delete z;
    size_--;

    if (y_original_color == BLACK && x != nullptr) {
      fixDelete(x);
    }
  }

  // fix tree after delete
  void fixDelete(BST_RB_Noode<T>* x) {
    if (x == nullptr) return;

    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        BST_RB_Noode<T>* sibling = x->parent->right;

        if (sibling == nullptr) break;

        // Case 1: sibling red
        if (sibling->color == RED) {
          sibling->color = BLACK;
          x->parent->color = RED;
          RotationLeft(x->parent);
          sibling = x->parent->right;
          if (sibling == nullptr) break;
        }

        bool leftChildBlack =
            (sibling->left == nullptr) || (sibling->left->color == BLACK);
        bool rightChildBlack =
            (sibling->right == nullptr) || (sibling->right->color == BLACK);

        // Case 2: two children if black
        if (leftChildBlack && rightChildBlack) {
          sibling->color = RED;
          x = x->parent;
        } else {
          // Case 3: left children sibling black
          if (rightChildBlack) {
            if (sibling->left != nullptr) {
              sibling->left->color = BLACK;
            }
            sibling->color = RED;
            RotationRight(sibling);
            sibling = x->parent->right;
            if (sibling == nullptr) break;
          }

          // Case 4: left children sibling black, right red
          sibling->color = x->parent->color;
          x->parent->color = BLACK;
          if (sibling->right != nullptr) {
            sibling->right->color = BLACK;
          }
          RotationLeft(x->parent);
          x = root;
        }
      } else {
        BST_RB_Noode<T>* sibling = x->parent->left;

        if (sibling == nullptr) break;

        if (sibling->color == RED) {
          sibling->color = BLACK;
          x->parent->color = RED;
          RotationRight(x->parent);
          sibling = x->parent->left;
          if (sibling == nullptr) break;
        }

        bool leftChildBlack =
            (sibling->left == nullptr) || (sibling->left->color == BLACK);
        bool rightChildBlack =
            (sibling->right == nullptr) || (sibling->right->color == BLACK);

        if (leftChildBlack && rightChildBlack) {
          sibling->color = RED;
          x = x->parent;
        } else {
          if (leftChildBlack) {
            if (sibling->right != nullptr) {
              sibling->right->color = BLACK;
            }
            sibling->color = RED;
            RotationLeft(sibling);
            sibling = x->parent->left;
            if (sibling == nullptr) break;
          }

          sibling->color = x->parent->color;
          x->parent->color = BLACK;
          if (sibling->left != nullptr) {
            sibling->left->color = BLACK;
          }
          RotationRight(x->parent);
          x = root;
        }
      }
    }

    if (x != nullptr) {
      x->color = BLACK;
    }
  }

 public:
  //--------------interface--------------
  set() : root{nullptr}, size_{0} {}

  set(std::initializer_list<value_type> const& items) : set() {
    for (const auto& item : items) {
      insert(item);
    }
  }

  set(const set& other) : root{nullptr}, size_{0} {
    if (other.root != nullptr) {
      root = copyTree(other.root, nullptr);
      size_ = other.size_;
    }
  }

  set(set&& other) noexcept : root(nullptr), size_(0) { swap(other); }

  set& operator=(set&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  void merge(set& other) {
    if (this == &other) return;

    set<T> buff;
    margeHelper(other.root, buff);
    margeBuff(buff);
    other.clear();
  }

  void swap(set& other) {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
  }

  ~set() { clear(); }

  SetIterator begin() { return SetIterator(findMin(root), root); }

  SetIterator end() { return SetIterator(nullptr, root); }

  SetConstIterator begin() const {
    return SetConstIterator(findMin(root), root);
  }

  void erase(SetIterator pos) {
    if (pos.current_ == nullptr || pos == end()) return;
    deleteNode(pos.current_);
  }

  SetConstIterator end() const { return SetConstIterator(nullptr, root); }

  SetIterator find(const T& key) {
    BST_RB_Noode<T>* node = findNode(root, key);
    return SetIterator(node, root);
  }

  SetConstIterator find(const T& key) const {
    BST_RB_Noode<T>* node = findNode(root, key);
    return SetConstIterator(node, root);
  }

  virtual bool contains(const T& key) const {
    return findNode(root, key) != nullptr;
  }

  //--------------Capacity--------------
  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(BST_RB_Noode<T>) / 2;
  }

  virtual std::pair<SetIterator, bool> insert(const value_type& v) {
    BST_RB_Noode<T>* existing = findNode(root, v);
    if (existing != nullptr) {
      return std::make_pair(SetIterator(existing, root), false);
    }

    if (root == nullptr) {
      root = new BST_RB_Noode<T>(v, BLACK);
      size_ = 1;
      BST_RB_Noode<T>* newNode = root;
      return std::make_pair(SetIterator(newNode, root), true);
    }

    BST_RB_Noode<T>* current = root;
    BST_RB_Noode<T>* parent = nullptr;

    while (current != nullptr) {
      parent = current;
      if (v == current->data) {
        return std::make_pair(SetIterator(current, root), false);
      } else if (v < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    BST_RB_Noode<T>* newNode = new BST_RB_Noode<T>(v, RED, parent);

    if (v < parent->data) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    fixInsertion(newNode);
    size_++;

    return std::make_pair(SetIterator(newNode, root), true);
  }

  bool search(const T& v) const {
    BST_RB_Noode<T>* current = root;
    while (current != nullptr) {
      if (current->data == v) {
        return true;
      }
      if (v < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return false;
  }

  void clear() {
    clearHelper(root);
    root = nullptr;
    size_ = 0;
  }

  void print() const {
    std::cout << "In order: ";
    inOrderHelper(root);
    std::cout << std::endl;
  }

  void printStructure() const {
    std::cout << "Tree Struct: " << std::endl;
    if (root == nullptr) {
      std::cout << "Tree Empty" << std::endl;
      return;
    }
    printStructureHelper(root, 0);
  }
};

// Операторы сравнения вынесены за класс
template <typename T>
bool operator==(const set<T>& lhs, const set<T>& rhs) {
  if (lhs.size() != rhs.size()) return false;

  auto it1 = lhs.begin();
  auto it2 = rhs.begin();

  while (it1 != lhs.end()) {
    if (*it1 != *it2) return false;
    ++it1;
    ++it2;
  }
  return true;
}

template <typename T>
bool operator<(const set<T>& lhs, const set<T>& rhs) {
  auto it1 = lhs.begin();
  auto it2 = rhs.begin();

  while (it1 != lhs.end() && it2 != rhs.end()) {
    if (*it1 < *it2) return true;
    if (*it1 > *it2) return false;
    ++it1;
    ++it2;
  }
  return it1 == lhs.end() && it2 != rhs.end();
}

template <typename T>
class set<T>::SetIterator {
  friend class set<T>;

 private:
  BST_RB_Noode<T>* current_;
  BST_RB_Noode<T>* root_;

 public:
  SetIterator(BST_RB_Noode<T>* cur = nullptr, BST_RB_Noode<T>* r = nullptr)
      : current_{cur}, root_{r} {}

  SetIterator(const SetIterator& other) = default;
  ~SetIterator() = default;
  SetIterator& operator=(const SetIterator& other) = default;

  T& operator*() {
    if (current_ == nullptr) {
      throw std::out_of_range("Dereferencing end iterator");
    }
    return current_->data;
  }

  T* operator->() {
    if (current_ == nullptr) {
      throw std::out_of_range("Accessing through end iterator");
    }
    return &(current_->data);
  }

  SetIterator& operator++() {
    if (current_ == nullptr) return *this;
    current_ = set<T>::findSuccessor(current_);
    return *this;
  }

  SetIterator operator++(int) {
    SetIterator temp = *this;
    ++(*this);
    return temp;
  }

  SetIterator& operator--() {
    if (current_ == nullptr) {
      current_ = set<T>::findMax(root_);
    } else {
      current_ = set<T>::findPredecessor(current_);
    }
    return *this;
  }

  SetIterator operator--(int) {
    SetIterator temp = *this;
    --(*this);
    return temp;
  }

  bool operator==(const SetIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const SetIterator& other) const { return !(*this == other); }

  operator SetConstIterator() const {
    return SetConstIterator(current_, root_);
  }
};

template <typename T>
class set<T>::SetConstIterator {
  friend class set<T>;

 private:
  const BST_RB_Noode<T>* current_;
  const BST_RB_Noode<T>* root_;

 public:
  SetConstIterator(const BST_RB_Noode<T>* cur = nullptr,
                   const BST_RB_Noode<T>* r = nullptr)
      : current_{cur}, root_{r} {}

  SetConstIterator(const SetIterator& other)
      : current_{other.current_}, root_{other.root_} {}

  SetConstIterator(const SetConstIterator& other) = default;
  ~SetConstIterator() = default;
  SetConstIterator& operator=(const SetConstIterator& other) = default;

  const T& operator*() const {
    if (current_ == nullptr) {
      throw std::out_of_range("Dereferencing end iterator");
    }
    return current_->data;
  }

  const T* operator->() const {
    if (current_ == nullptr) {
      throw std::out_of_range("Accessing through end iterator");
    }
    return &(current_->data);
  }

  SetConstIterator& operator++() {
    if (current_ == nullptr) return *this;
    current_ = set<T>::findSuccessor(const_cast<BST_RB_Noode<T>*>(current_));
    return *this;
  }

  SetConstIterator operator++(int) {
    SetConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  SetConstIterator& operator--() {
    if (current_ == nullptr) {
      current_ = set<T>::findMax(const_cast<BST_RB_Noode<T>*>(root_));
    } else {
      current_ =
          set<T>::findPredecessor(const_cast<BST_RB_Noode<T>*>(current_));
    }
    return *this;
  }

  SetConstIterator operator--(int) {
    SetConstIterator temp = *this;
    --(*this);
    return temp;
  }

  bool operator==(const SetConstIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const SetConstIterator& other) const {
    return !(*this == other);
  }
};

};  // namespace s21_containers

#endif  // SET_H