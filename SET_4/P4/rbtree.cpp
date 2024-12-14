#include "rbtree.h"
#include <iostream>

Node::Node(int value) : key(value), height(1), size(1),
                        left(nullptr), right(nullptr), parent(nullptr),
                        color(Color::RED) {
}

RBTree::RBTree() : root(nullptr) {
}

RBTree::RBTree(std::initializer_list<int> list) : root(nullptr) {
  for (auto el : list) {
    insert(el);
  }
}

void clear(Node* node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

RBTree::~RBTree() {
  clear(root);
}

int getNodeSize(Node* node) {
  return node ? node->size : 0;
}

int getNodeHeight(Node* node) {
  return node ? node->height : 0;
}

int* RBTree::find(int key) {
  Node* cur = root;
  while (cur != nullptr) {
    if (key == cur->key) {
      return &cur->key;
    } else if (key < cur->key) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return nullptr;
}

void fixNode(Node* node) {
  if (node != nullptr) {
    node->size = getNodeSize(node->left) + getNodeSize(node->right) + 1;
    node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    if (node->color == Color::BLACK) {
      ++node->height;
    }
  }
}

void leftRotate(Node*& node, Node*& root) {
  Node* child = node->right;
  node->right = child->left;
  if (node->right != nullptr)
    node->right->parent = node;
  child->parent = node->parent;
  if (node->parent == nullptr)
    root = child;
  else if (node == node->parent->left)
    node->parent->left = child;
  else
    node->parent->right = child;
  child->left = node;
  node->parent = child;

  fixNode(node);
  fixNode(child);
}

void rightRotate(Node*& node, Node*& root) {
  Node* child = node->left;
  node->left = child->right;
  if (node->left != nullptr)
    node->left->parent = node;
  child->parent = node->parent;
  if (node->parent == nullptr)
    root = child;
  else if (node == node->parent->left)
    node->parent->left = child;
  else
    node->parent->right = child;
  child->right = node;
  node->parent = child;

  fixNode(node);
  fixNode(child);
}

void fixInsert(Node* &node, Node*& root) {
  Node* parent = nullptr;
  Node* grandparent = nullptr;
  while (node != root && node->color == Color::RED && node->parent->color == Color::RED) {
    parent = node->parent;
    grandparent = parent->parent;
    if (parent == grandparent->left) {
      Node* uncle = grandparent->right;
      if (uncle != nullptr && uncle->color == Color::RED) {
        grandparent->color = Color::RED;
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node = grandparent;
      }
      else {
        if (node == parent->right) {
          leftRotate(parent, root);
          node = parent;
          parent = node->parent;
        }
        rightRotate(grandparent, root);
        std::swap(parent->color, grandparent->color);
        node = parent;
      }
    }
    else {
      Node* uncle = grandparent->left;
      if (uncle != nullptr && uncle->color == Color::RED) {
        grandparent->color = Color::RED;
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node = grandparent;
      }
      else {
        if (node == parent->left) {
          rightRotate(parent, root);
          node = parent;
          parent = node->parent;
        }
        leftRotate(grandparent, root);
        std::swap(parent->color, grandparent->color);
        node = parent;
      }
    }
  }
  root->color = Color::BLACK;
}

void RBTree::insert(int key) {
  if (find(key) != nullptr) {
    return;
  }
  if (root == nullptr) {
    root = new Node(key);
    root->color = Color::BLACK;
    return;
  }
  Node* node = new Node(key);
  Node* parent = nullptr;
  Node* current = root;
  while (current != nullptr) {
    parent = current;
    if (node->key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  node->parent = parent;
  if (node->key < parent->key)
    parent->left = node;
  else
    parent->right = node;

  Node *tmp = node;
  while (tmp != nullptr) {
    fixNode(tmp);
    tmp = tmp->parent;
  }
  fixInsert(node, root);
}

int* RBTree::lowerBound(int key) {
  Node* cur = root;
  Node* ans = nullptr;
  while (cur != nullptr) {
    if (key <= cur->key) {
      ans = cur;
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return ans ? &ans->key : nullptr;
}

int RBTree::size() const {
  return root ? root->size : 0;
}

bool RBTree::empty() const {
  return size() == 0;
}

int RBTree::height() const {
  return root ? root->height : 0;
}
