#include "rbtree.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void inOrderTraversal(Node *node, std::vector<int> &values) {
  if (node) {
    inOrderTraversal(node->left, values);
    values.push_back(node->key);
    inOrderTraversal(node->right, values);
  }
}

bool isBST(Node *node, int minVal, int maxVal) {
  if (!node) return true;
  if (node->key < minVal || node->key > maxVal) return false;
  return isBST(node->left, minVal, node->key) && isBST(node->right, node->key, maxVal);
}

bool isRedBlackTree(Node *node, int &blackCount, int currentBlackCount = 0) {
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

void test1() {
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

  std::cout << "Test 1 passed!" << std::endl;
}

void printHelper(Node *root, std::string indent, bool last) {
  if (root != nullptr) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }
    std::string sColor = (root->color == Color::RED) ? "RED" : "BLACK";
    std::cout << root->key << " (" << &root->key << ")" << std::endl;
    printHelper(root->left, indent, false);
    printHelper(root->right, indent, true);
  }
}

void printTree(Node *root) {
  if (root == nullptr)
    std::cout << "Tree is empty." << std::endl;
  else {
    std::cout << "Red-Black Tree:" << std::endl;
    printHelper(root, "", true);
  }
}

void test2() {
  RBTree tree({1, 4, 5, 100});
  tree.insert(12);
  tree.insert(12);
  tree.insert(20);

  printTree(tree.root);
  tree.insert(2);
  printTree(tree.root);
  std::cout << std::endl;
}

void test3() {
  auto list = {10, 20, 30, 40, 50};
  RBTree tree(list);
  printTree(tree.root);

  for (auto el : list) {
    std::cout << "Find " << el << ' ' << tree.find(el) << std::endl;
  }
  tree.insert(10);
  tree.insert(20);
  printTree(tree.root);
  std::cout << "Find " << 10 << ' ' << tree.find(10) << std::endl;
  std::cout << "Find " << 20 << ' ' << tree.find(20) << std::endl;
}

void test4() {
  RBTree tree;

  std::cout << "Test 1" << std::endl;
  if (tree.size() != 0) {
    std::cout << "Error: size = 0, but size = " << tree.size() << std::endl;
  } else {
    std::cout << "Good: size = 0" << std::endl;
  }

  std::cout << "Test 2" << std::endl;
  tree.insert(10);
  if (tree.size() != 1) {
    std::cout << "Error: size = 1, but size = " << tree.size() << std::endl;
  } else {
    std::cout << "Good: size = 1" << std::endl;
  }

  std::cout << "Test 3" << std::endl;
  tree.insert(20);
  if (tree.size() != 2) {
    std::cout << "Error: size = 2, but size = " << tree.size() << std::endl;
  } else {
    std::cout << "Good: size = 2" << std::endl;
  }

  std::cout << "Test 4" << std::endl;
  tree.insert(30);
  if (tree.size() != 3) {
    std::cout << "Error: size = 3, but size = " << tree.size() << std::endl;
  } else {
    std::cout << "Good: size = 3" << std::endl;
  }

  std::cout << "Test 5" << std::endl;
  tree.insert(20);
  if (tree.size() != 3) {
    std::cout << "Error: size = 3, but size = " << tree.size() << std::endl;
  } else {
    std::cout << "Good: size = 3" << std::endl;
  }

  std::cout << "Test 6" << std::endl;
  tree.insert(15);
  if (tree.size() != 4) {
    std::cout << "Error: size = 4, but size = " << tree.size() << std::endl;
  } else {
    std::cout << "Good: size = 4" << std::endl;
  }

  std::cout << "Test 7" << std::endl;
  tree.insert(25);
  if (tree.size() != 5) {
    std::cout << "Error: size = 5, but size = " << tree.size() << std::endl;
  } else {
    std::cout << "Good: size = 5" << std::endl;
  }
}

int main() {
  test4();
  return 0;
}
