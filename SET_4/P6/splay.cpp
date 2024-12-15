#include <iostream>
#include "splay-tree.h"

Node::Node(int key, Node *parent) : key(key), left(nullptr), right(nullptr), parent(parent) {
}

SplayTree::SplayTree() : root(nullptr) {
}

void SplayTree::clear(Node *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

SplayTree::~SplayTree() {
  clear(root);
}

void SplayTree::insert(int key) {
  if (find(key) != nullptr) {
    return;
  }
  if (root == nullptr) {
    root = new Node(key, nullptr);
    return;
  }

  Node* cur = root;
  Node* par = nullptr;
  while (cur) {
    par = cur;
    if (key < cur->key) {
      cur = cur->left;
    } else if (key > cur->key) {
      cur = cur->right;
    }
  }

  if (key < par->key) {
    par->left = new Node(key, par);
  } else {
    par->right = new Node(key, par);
  }
}

Node *SplayTree::find(int key) const {
  Node* cur = root;
  while(cur) {
    if (key < cur->key) {
      cur = cur->left;
    } else if (key > cur->key) {
      cur = cur->right;
    } else {
      return cur;
    }
  }
  return nullptr;
}

void SplayTree::rotateLeft(Node *node) {
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
}

void SplayTree::rotateRight(Node *node) {
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
}

int SplayTree::splay(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  int rotations = 0;
  while (node->parent) {
    if (!node->parent->parent) {
      if (node->parent->left == node)
        rotateRight(node->parent);
      else
        rotateLeft(node->parent);
      rotations += 1;
    } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
      rotateRight(node->parent->parent);
      rotateRight(node->parent);
      rotations += 2;
    } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
      rotateLeft(node->parent->parent);
      rotateLeft(node->parent);
      rotations += 2;
    } else {
      if (node->parent->left == node && node->parent->parent->right == node->parent) {
        rotateRight(node->parent);
        rotateLeft(node->parent);
      } else {
        rotateLeft(node->parent);
        rotateRight(node->parent);
      }
      rotations += 1;
    }
  }
  root = node;
  return rotations;
}

int SplayTree::getHeight(Node* node) const {
  if (node == nullptr){
    return -1;
  }
  return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

int SplayTree::getHeight() const {
  return getHeight(root);
}
