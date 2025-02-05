#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>

using namespace std;

template<class KeyType, class ValueType>
struct Node {
  KeyType key;
  ValueType value;
  Node *next;

  Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
};

template<class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
 public:
  HashTable() : size_(0), capacity_(100), loadFactor_(0.5), hasher_(Func()) {
    table.resize(capacity_, nullptr);
  }

  HashTable(const Func &hasher) : size_(0), capacity_(100), loadFactor_(0.5), hasher_(hasher) {
    table.resize(capacity_, nullptr);
  }

  HashTable(const size_t &capacity, const double &loadFactor, const Func &hasher = Func())
      : size_(0), capacity_(capacity), loadFactor_(loadFactor), hasher_(hasher) {
    if (loadFactor <= 0 || loadFactor > 1) {
      loadFactor_ = 0.5;
    }
    table.resize(capacity_, nullptr);
  }

  ~HashTable() {
    for (size_t i = 0; i < capacity_; ++i) {
      Node<KeyType, ValueType> *cur = table[i];
      while (cur != nullptr) {
        Node<KeyType, ValueType> *next = cur->next;
        delete cur;
        cur = next;
      }
      table[i] = nullptr;
    }
  }

  int size() const {
    return size_;
  }

  int capacity() const {
    return capacity_;
  }

  Node<KeyType, ValueType> &operator[](uint64_t hash) const {
    if (hash >= capacity_) {
      throw std::out_of_range("Hash out of range");
    }
    if (table[hash] == nullptr) {
      throw std::runtime_error("Element is nullptr");
    }
    return *table[hash];
  }

  Node<KeyType, ValueType> at(uint64_t hash) const {
    if (hash >= capacity_) {
      throw std::out_of_range("Hash out of range");
    }
    if (table[hash] == nullptr) {
      throw std::runtime_error("Element is nullptr");
    }
    return *table[hash];
  }

  void insert(const KeyType &key, const ValueType &value) {
    size_t pos = getPosition(key);
    Node<KeyType, ValueType> *cur = table[pos];
    Node<KeyType, ValueType> *prev = nullptr;

    while (cur != nullptr) {
      if (cur->key == key) {
        cur->value = value;
        return;
      }
      prev = cur;
      cur = cur->next;
    }

    auto newNode = new Node<KeyType, ValueType>(key, value);
    if (prev == nullptr) {
      table[pos] = newNode;
    } else {
      prev->next = newNode;
    }

    ++size_;
    if (size_ > capacity_ * loadFactor_) {
      rehash();
    }
  }

  void erase(const KeyType &key) {
    size_t pos = getPosition(key);
    Node<KeyType, ValueType> *cur = table[pos];
    Node<KeyType, ValueType> *prev = nullptr;

    while (cur != nullptr) {
      if (cur->key == key) {
        if (prev == nullptr) {
          table[pos] = cur->next;
        } else {
          prev->next = cur->next;
        }
        delete cur;
        --size_;
        return;
      }
      prev = cur;
      cur = cur->next;
    }
  }

  ValueType *find(const KeyType &key) {
    size_t pos = getPosition(key);
    Node<KeyType, ValueType> *cur = table[pos];

    while (cur != nullptr) {
      if (cur->key == key) {
        return &cur->value;
      }
      cur = cur->next;
    }

    return nullptr;
  }

 private:
  std::vector<Node<KeyType, ValueType> *> table;
  size_t capacity_;
  size_t size_;
  double loadFactor_;
  Func hasher_;

  size_t getPosition(const KeyType &key) {
    return hasher_(key) % capacity_;
  }

  void rehash() {
    size_t newCapacity = capacity_ * 2;
    std::vector<Node<KeyType, ValueType> *> newTable(newCapacity, nullptr);

    for (size_t i = 0; i < capacity_; ++i) {
      Node<KeyType, ValueType> *current = table[i];
      while (current != nullptr) {
        Node<KeyType, ValueType> *next = current->next;

        size_t newPos = hasher_(current->key) % newCapacity;
        current->next = newTable[newPos];
        newTable[newPos] = current;

        current = next;
      }
    }

    table.swap(newTable);
    capacity_ = newCapacity;
  }
};

int main() {
  HashTable<std::string, int> ht;

  ht.insert("apple", 10);
  ht.insert("banana", 20);
  ht.insert("cherry", 30);

  std::cout << "Size: " << ht.size() << std::endl;
  std::cout << "Capacity: " << ht.capacity() << std::endl;

  int *value = ht.find("banana");
  if (value) {
    std::cout << "Value for 'banana': " << *value << std::endl;
  }

  ht.erase("banana");
  std::cout << "Size after erase: " << ht.size() << std::endl;

  return 0;
}