#include "rbtree.h"
#include <iostream>

Node::Node(int value) {
  key = value;
  height = 1;
  size = 1;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  color = Color::RED;
}

RBTree::RBTree() {
  root = nullptr;
}

RBTree::RBTree(std::initializer_list<int> list){
  for (auto el : list) {
    insert(el);
  }
}

RBTree::~RBTree(){
  while (size() > 0) {
    erase(root->key);
  }
}

int getNodeSize(Node *node){
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

void fixSize(Node *node) {
  if (node != nullptr) {
    fixSize(node->left);
    fixSize(node->right);
    node->size = getNodeSize(node->left) + getNodeSize(node->right) + 1;
  }
}

int getNodeHeight(Node *node){
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

void fixHeight(Node *node) {
  if (node != nullptr) {
    fixHeight(node->left);
    fixHeight(node->right);
    node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    if (node->color == Color::BLACK) {
      ++node->height;
    }
  }
}

int *RBTree::find(int key){
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

void leftRotate(Node* node, Node* root) {
  auto tmp_r = node->right;
  node->right = tmp_r->left;
  if (tmp_r->left != nullptr) {
    tmp_r->left->parent = node;
  }
  tmp_r->parent = node->parent;
  if (node->parent == nullptr) {
    root = tmp_r;
  } else if (node == node->parent->left) {
    node->parent->left = tmp_r;
  } else {
    node->parent->right = tmp_r;
  }
  tmp_r->left = node;
  node->parent = tmp_r;
}

void rightRotate(Node* node, Node* root) {
  auto tmp_l = node->left;
  node->left = tmp_l->right;
  if (tmp_l->right != nullptr) {
    tmp_l->right->parent = node;
  }
  tmp_l->parent = node->parent;
  if (node->parent == nullptr) {
    root = tmp_l;
  } else if (node == node->parent->right) {
    node->parent->right = tmp_l;
  } else {
    node->parent->left = tmp_l;
  }
  tmp_l->right = node;
  node->parent = tmp_l;
}

void fixInsert(Node* node, Node* root){
  while (node != nullptr && node != root && node->parent->color == Color::RED){
    Node *uncle;
    if (node->parent == node->parent->parent->left) {
      uncle = node->parent->parent->right;
    } else {
      uncle = node->parent->parent->left;
    }
    if (uncle->color == Color::RED) {
      node->parent->color = Color::BLACK;
      uncle->color = Color::BLACK;
      node->parent->parent->color = Color::RED;
    } else {
      if (node == node->parent->right) {
        node = node->parent;
        leftRotate(node, root);
      } else if (node == node->parent->left){
        node = node->parent;
        rightRotate(node, root);
      }
      node->parent->color = Color::BLACK;
      node->parent->parent->color = Color::RED;
      if (node->parent == node->parent->parent->left) {
        rightRotate(node->parent->parent, root);
      } else {
        leftRotate(node->parent->parent, root);
      }
    }
  }
  if (node != nullptr) {
    root->color = Color::BLACK;
  }
}

void RBTree::insert(int key){
  if (find(key) != nullptr) {
    return;
  }
  if (root == nullptr) {
    root = new Node(key);
    root->color = Color::BLACK;
    return;
  }

  Node *cur = root, *prev = nullptr;
  while (cur != nullptr) {
    prev = cur;
    if (key < cur->key) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }

  if (key < prev->key) {
    prev->left = new Node(key);
    prev->left->parent = prev;
    fixInsert(prev->left, root);
  } else {
    prev->right = new Node(key);
    prev->right->parent = prev;
    fixInsert(prev->right, root);
  }
  fixHeight(root);
  fixSize(root);
}

void transplant(Node *&root, Node *&u, Node *&v) {
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

Node *minValueNode(Node* node) {
  Node *cur = node;
  while (cur->left != nullptr)
    cur = cur->left;
  return cur;
}

void fixDelete(Node *node, Node* root) {
  while (node != nullptr && node != root && node->color == Color::BLACK) {
    if (node == node->parent->left) {
      Node* sibling = node->parent->right;
      if (sibling->color == Color::RED) {
        sibling->color = Color::BLACK;
        node->parent->color = Color::RED;
        leftRotate(node->parent, root);
        sibling = node->parent->right;
      }
      if ((sibling->left == nullptr || sibling->left->color == Color::BLACK)
          && (sibling->right == nullptr || sibling->right->color == Color::BLACK)) {
        sibling->color = Color::RED;
        node = node->parent;
      }
      else {
        if (sibling->right == nullptr || sibling->right->color == Color::BLACK) {
          if (sibling->left != nullptr) {
            sibling->left->color = Color::BLACK;
          }
          sibling->color = Color::RED;
          rightRotate(sibling, root);
          sibling = node->parent->right;
        }
        sibling->color = node->parent->color;
        node->parent->color = Color::BLACK;
        if (sibling->right != nullptr) {
          sibling->right->color = Color::BLACK;
        }
        leftRotate(node->parent, root);
        node = root;
      }
    }
    else {
      Node* sibling = node->parent->left;
      if (sibling->color == Color::RED) {
        sibling->color = Color::BLACK;
        node->parent->color = Color::RED;
        rightRotate(node->parent, root);
        sibling = node->parent->left;
      }
      if ((sibling->left == nullptr || sibling->left->color == Color::BLACK)
          && (sibling->right == nullptr || sibling->right->color == Color::BLACK)) {
        sibling->color = Color::RED;
        node = node->parent;
      }
      else {
        if (sibling->left == nullptr || sibling->left->color == Color::BLACK) {
          if (sibling->right != nullptr) {
            sibling->right->color = Color::BLACK;
          }
          sibling->color = Color::RED;
          leftRotate(sibling, root);
          sibling = node->parent->left;
        }
        sibling->color = node->parent->color;
        node->parent->color = Color::BLACK;
        if (sibling->left != nullptr) {
          sibling->left->color = Color::BLACK;
        }
        rightRotate(node->parent, root);
        node = root;
      }
    }
  }
  if (node != nullptr) {
    node->color = Color::BLACK;
  }
}

void RBTree::erase(int key){
  Node *cur = root, *deleted_node = nullptr;
  while (cur != nullptr) {
    if (key > cur->key) {
      cur = cur->right;
    } else if (key < cur->key){
      cur = cur->left;
    } else {
      deleted_node = cur;
      break;
    }
  }
  if (deleted_node == nullptr) {
    return;
  }

  Node* son = nullptr;
  auto originalColor = deleted_node->color;
  if (deleted_node->left == nullptr) {
    son = deleted_node->right;
    transplant(root, deleted_node, deleted_node->right);
  }
  else if (deleted_node->right == nullptr) {
    son = deleted_node->left;
    transplant(root, deleted_node, deleted_node->left);
  }
  else {
    Node *minNode = minValueNode(deleted_node->right);
    originalColor = minNode->color;
    son = minNode->right;
    if (minNode->parent == deleted_node) {
      if (son != nullptr)
        son->parent = minNode;
    }
    else {
      transplant(root, minNode, minNode->right);
      minNode->right = deleted_node->right;
      minNode->right->parent = minNode;
    }
    transplant(root, deleted_node, minNode);
    minNode->left = deleted_node->left;
    minNode->left->parent = minNode;
    minNode->color = deleted_node->color;
  }
  delete deleted_node;
  if (originalColor == Color::BLACK) {
    fixDelete(son, root);
  }
  fixHeight(root);
  fixSize(root);
}

int *RBTree::lowerBound(int key) {
  Node *cur = root;
  Node *ans = nullptr;
  while (cur != nullptr) {
    if (key <= cur->key) {
      ans = cur;
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  if (ans == nullptr){
    return nullptr;
  }
  return &ans->key;
}

int RBTree::size() const {
  if (root == nullptr){
    return 0;
  }
  fixSize(root);
  return root->size;
}

bool RBTree::empty() const {
  return (size() == 0);
}

int RBTree::height() const {
  if (root == nullptr) {
    return 0;
  }
  return root->height;
}