#include "rbtree.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void inOrderTraversal(Node* node, std::vector<int>& values) {
  if (node) {
    inOrderTraversal(node->left, values);
    values.push_back(node->key);
    inOrderTraversal(node->right, values);
  }
}

bool isBST(Node* node, int minVal, int maxVal) {
  if (!node) return true;
  if (node->key < minVal || node->key > maxVal) return false;
  return isBST(node->left, minVal, node->key) && isBST(node->right, node->key, maxVal);
}

bool isRedBlackTree(Node* node, int& blackCount, int currentBlackCount = 0) {
  if (!node) {
    if (blackCount == -1) {
      blackCount = currentBlackCount;
    } else if (blackCount != currentBlackCount) {
      return false;
    }
    return true;
  }

  if (node->color == Color::RED) {
    if ((node->left && node->left->color == Color::RED) || (node->right && node->right->color == Color::RED)) {
      return false; // Два красных узла подряд
    }
  }

  if (node->color == Color::BLACK) {
    currentBlackCount++;
  }

  return isRedBlackTree(node->left, blackCount, currentBlackCount) &&
      isRedBlackTree(node->right, blackCount, currentBlackCount);
}

void testRBTree() {
  RBTree tree;

  // Вставляем элементы
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(15);
  tree.insert(25);

  // Проверяем, что дерево не пустое
  assert(!tree.empty());
  // Проверяем размер дерева
  assert(tree.size() == 5);

  // Проверяем правильность обхода in-order
  std::vector<int> values;
  inOrderTraversal(tree.root, values);
  std::vector<int> expected = {10, 15, 20, 25, 30};
  assert(values == expected);

  // Проверяем, что дерево является бинарным деревом поиска
  assert(isBST(tree.root, INT_MIN, INT_MAX));

  // Проверяем свойства красно-черного дерева
  int blackCount = -1;
  assert(isRedBlackTree(tree.root, blackCount));

  std::cout << "Все тесты пройдены успешно!" << std::endl;
}

int main() {
  testRBTree();
  return 0;
}
