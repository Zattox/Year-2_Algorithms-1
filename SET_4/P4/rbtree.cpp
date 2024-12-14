#include "rbtree.h"
#include <iostream>

Node::Node(int value) : key(value), height(1), size(1), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {
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

void fixSize(Node* &node) {
  if (node != nullptr) {
    fixSize(node->left);
    fixSize(node->right);
    node->size = getNodeSize(node->left) + getNodeSize(node->right) + 1;
  }
}

int getNodeHeight(Node* node) {
  return node ? node->height : 0;
}

void fixHeight(Node* node) {
  if (node != nullptr) {
    fixHeight(node->left);
    fixHeight(node->right);
    node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    if (node->color == Color::BLACK) {
      ++node->height;
    }
  }
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

void leftRotate(Node*& node, Node*& root) {
  Node* tmp_r = node->right;
  if (tmp_r == nullptr) return; // Проверка на nullptr

  node->right = tmp_r->left;
  if (tmp_r->left != nullptr) {
    tmp_r->left->parent = node;
  }
  tmp_r->parent = node->parent;
  if (node->parent == nullptr) {
    root = tmp_r; // Если node был корнем, обновляем корень
  } else if (node == node->parent->left) {
    node->parent->left = tmp_r;
  } else {
    node->parent->right = tmp_r;
  }
  tmp_r->left = node;
  node->parent = tmp_r;
}

void rightRotate(Node*& node, Node*& root) {
  Node* tmp_l = node->left;
  if (tmp_l == nullptr) return; // Проверка на nullptr

  node->left = tmp_l->right;
  if (tmp_l->right != nullptr) {
    tmp_l->right->parent = node;
  }
  tmp_l->parent = node->parent;
  if (node->parent == nullptr) {
    root = tmp_l; // Если node был корнем, обновляем корень
  } else if (node == node->parent->right) {
    node->parent->right = tmp_l;
  } else {
    node->parent->left = tmp_l;
  }
  tmp_l->right = node;
  node->parent = tmp_l;
}

void fixInsert(Node* &node, Node*& root) {
  while (node != nullptr && node->parent != nullptr && node->parent->color == Color::RED) {
    Node* uncle = nullptr;
    if (node->parent == node->parent->parent->left) {
      uncle = node->parent->parent->right;
      if (uncle != nullptr && uncle->color == Color::RED) {
        // Случай 1: дядя красный
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        node = node->parent->parent;
      } else {
        // Случай 2: дядя черный, текущий узел правый
        if (node == node->parent->right) {
          node = node->parent;
          leftRotate(node, root);
        }
        // Случай 3: дядя черный, текущий узел левый
        if (node->parent->parent != nullptr) { // Добавлена проверка на nullptr
          node->parent->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          rightRotate(node->parent->parent, root);
        }
      }
    } else {
      uncle = node->parent->parent->left;
      if (uncle != nullptr && uncle->color == Color::RED) {
        // Случай 1: дядя красный
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node->parent->parent->color = Color::RED;
        node = node->parent->parent;
      } else {
        // Случай 2: дядя черный, текущий узел левый
        if (node == node->parent->left) {
          node = node->parent;
          rightRotate(node, root);
        }
        // Случай 3: дядя черный, текущий узел правый
        if (node->parent->parent != nullptr) { // Добавлена проверка на nullptr
          node->parent->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          leftRotate(node->parent->parent, root);
        }
      }
    }
  }
  if (root != nullptr) {
    root->color = Color::BLACK; // Корень всегда черный
  }
}

void RBTree::insert(int key) {
  if (find(key) != nullptr) {
    return; // Если ключ уже существует, ничего не делаем
  }
  if (root == nullptr) {
    root = new Node(key);
    root->color = Color::BLACK; // Корень черный
    return;
  }

  Node* cur = root;
  Node* prev = nullptr;
  while (cur != nullptr) {
    prev = cur;
    if (key < cur->key) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }

  Node* newNode = new Node(key);
  newNode->parent = prev; // Устанавливаем родителя
  if (key < prev->key) {
    prev->left = newNode;
  } else {
    prev->right = newNode;
  }

  // Восстанавливаем свойства красно-черного дерева
  fixInsert(newNode, root);
  fixHeight(root);
  fixSize(root);
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
