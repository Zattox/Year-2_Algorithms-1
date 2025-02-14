#include <iostream>
#include "avl_tree.h"

Node::Node(int value) {
  this->value = value;
  height = 1;
  left = nullptr;
  right = nullptr;
}

Node::~Node() {}

AVLTree::AVLTree() {
  root_ = nullptr;
  size_ = 0;

}

AVLTree::AVLTree(int value) {
  root_ = new Node(value);
  size_ = 1;
}

int AVLTree::getHeight() {
  if (!root_) {
    return 0;
  }
  return root_->height;
}

void AVLTree::insert(int value) {
  if (find(value) != nullptr) {
    return;
  }
  root_ = insertNode(root_, value);
  ++size_;
}

void AVLTree::erase(int value) {
  if (find(value) == nullptr) {
    return;
  }
  root_ = removeNode(root_, value);
  --size_;
}

int *AVLTree::find(int value) {
  auto node = findNode(root_, value);
  if (node == nullptr) {
    return nullptr;
  }
  return &node->value;
}

int *AVLTree::traversal() {
  int *array = new int[size_];
  int *index = new int(0);
  traversalInternal(root_, array, index);
  delete index;
  return array;
}

int *AVLTree::lowerBound(int value) {
  auto node = lowerBoundInternal(root_, value);
  if (node == nullptr || node->value < value) {
    return nullptr;
  }
  return &node->value;
}

bool AVLTree::empty() {
  if (root_ == nullptr || size_ == 0) {
    return true;
  }
  return false;
}

Node *AVLTree::getRoot() {
  return root_;
}

int AVLTree::getSize() {
  return size_;
}

AVLTree::~AVLTree() {
  while (size_ > 0) {
    erase(root_->value);
  }
}

int AVLTree::getNodeHeight(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVLTree::balanceFactor(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return getNodeHeight(node->right) - getNodeHeight(node->left);
}

void AVLTree::balanceHeight(Node *node) {
  int h_left = getNodeHeight(node->left);
  int h_right = getNodeHeight(node->right);
  node->height = std::max(h_left, h_right) + 1;
}

Node *AVLTree::rotateRight(Node *node) {
  auto tmp = node->left;
  node->left = tmp->right;
  tmp->right = node;
  balanceHeight(node);
  balanceHeight(tmp);
  return tmp;
}

Node *AVLTree::rotateLeft(Node *node) {
  auto tmp = node->right;
  node->right = tmp->left;
  tmp->left = node;
  balanceHeight(node);
  balanceHeight(tmp);
  return tmp;
}

Node *AVLTree::balanceNode(Node *node) {
  balanceHeight(node);
  if (balanceFactor(node) == 2){
    if (balanceFactor(node->right) < 0) {
      node->right = rotateRight(node->right);
    }
    return rotateLeft(node);
  }
  if (balanceFactor(node) == -2){
    if (balanceFactor(node->left) > 0) {
      node->left = rotateLeft(node->left);
    }
    return rotateRight(node);
  }
  return node;
}

Node *AVLTree::insertNode(Node *node, int value) {
  if (!node) {
    return new Node(value);
  }
  if (value < node->value) {
    node->left = insertNode(node->left, value);
  } else {
    node->right = insertNode(node->right, value);
  }
  return balanceNode(node);
}

Node *AVLTree::findMinNode(Node *node) {
  if (node->left == nullptr){
    return node;
  }
  return findMinNode(node->left);
}

Node *AVLTree::removeMinNode(Node *node) {
  if (node->left == nullptr) {
    return node->right;
  }
  node->left = removeMinNode(node->left);
  return balanceNode(node);
}

Node *AVLTree::removeNode(Node *node, int value) {
  if (!node) {
    return nullptr;
  }
  if (value < node->value) {
    node->left = removeNode(node->left, value);
  } else if (value > node->value){
    node->right = removeNode(node->right, value);
  } else {
    auto tmp_l = node->left;
    auto tmp_r = node->right;
    delete node;
    if (!tmp_r) {
      return tmp_l;
    }
    auto mini = findMinNode(tmp_r);
    mini->right = removeMinNode(tmp_r);
    mini->left = tmp_l;
    return balanceNode(mini);
  }
  return balanceNode(node);
}

Node *AVLTree::findNode(Node *node, int value) {
  if (node == nullptr) {
    return nullptr;
  }
  totalFindOperations++;
  if (value < node->value) {
    return findNode(node->left, value);
  } else if (value > node->value) {
    return findNode(node->right, value);
  } else {
    return node;
  }
}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {
  if (node == nullptr) {
    return;
  }
  traversalInternal(node->left, array, index);
  array[*index] = node->value;
  *index += 1;
  traversalInternal(node->right, array, index);
}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {
  if (value < current->value) {
    if (current->left == nullptr) {
      return current;
    }
    return lowerBoundInternal(current->left, value);
  } else if (value > current->value) {
    if (current->right == nullptr) {
      return current;
    }
    return lowerBoundInternal(current->right, value);
  } else {
    return current;
  }
}