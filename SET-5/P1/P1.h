//
// Created by dumpl on 05.02.2025.
//

#ifndef SET_5_SET_5_P1_P1_H_
#define SET_5_SET_5_P1_P1_H_

#include <iostream>
#include <cstdint>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
  KeyType key;
  ValueType value;
  Node *next;

  Node(KeyType, ValueType);
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
 public:
  HashTable();
  HashTable(Func);
  HashTable(size_t, double, Func = std::hash<KeyType>());

  ~HashTable();

  void insert(KeyType, ValueType);
  ValueType *find(KeyType);
  void erase(KeyType);

  Node<KeyType, ValueType> &operator[](uint64_t);
  Node<KeyType, ValueType> at(uint64_t);

  int size() const;
  int capacity() const;
};


#endif //SET_5_SET_5_P1_P1_H_
