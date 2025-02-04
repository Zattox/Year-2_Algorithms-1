#include "btree.h"
#include <iostream>
#include <vector>

Node::Node(int t) : parent(nullptr), isLeaf(true), t(t) {
  key.reserve(2 * t - 1);
  children.reserve(2 * t);
}

BTree::BTree(int t) : t_(t), size_(1) {
  root = new Node(t);
}

void clear(Node* node) {
  if (node != nullptr) {
    for (auto child : node->children) {
      clear(child);
    }
    delete node;
  }
}

BTree::~BTree() {
  clear(root);
}

void SplitChild(Node* &x, int i, int t) {
  Node* y = x->children[i];
  Node* z = new Node(t);
  z->isLeaf = y->isLeaf;
  z->parent = y->parent;

  while (y->key.size() > t) {
    z->key.push_back(y->key.back());
    y->key.pop_back();
  }
  std::reverse(z->key.begin(), z->key.end());

  if (!y->isLeaf) {
    while (y->children.size() > t) {
      z->children.push_back(y->children.back());
      y->children.pop_back();
    }
    std::reverse(z->children.begin(), z->children.end());
  }

  x->children.insert(x->children.begin() + i + 1, z);
  x->key.insert(x->key.begin() + i, y->key[t - 1]);
  y->key.pop_back();
}

void InsertNonfull(Node* &x, int key, int t, int &cntOfSplit) {
  int i = x->key.size() - 1;
  if (x->isLeaf) {
    while (i >= 0 && key < x->key[i]) {
      --i;
    }
    x->key.insert(x->key.begin() + i + 1, key);
  } else {
    while (i >= 0 && key < x->key[i]) {
      --i;
    }
    ++i;
    if (i < x->children.size() && x->children[i]->key.size() == 2 * t - 1) {
      SplitChild(x, i, t);
      ++cntOfSplit;
      if (key > x->key[i]) {
        ++i;
      }
    }
    InsertNonfull(x->children[i], key, t, cntOfSplit);
  }
}

Node *find(Node *x, int key) {
  for (auto el : x->key) {
    if (el == key) {
      return x;
    }
  }
  for (auto el : x->children) {
    auto nd = find(el, key);
    if (nd != nullptr) {
      return nd;
    }
  }
  return nullptr;
}

void BTree::insert(int key) {
  if (find(root, key) != nullptr) {
    return;
  }

  if (root->key.size() == 2 * t_ - 1) {
    Node* new_root = new Node(t_);
    new_root->isLeaf = false;
    new_root->children.push_back(root);
    root->parent = new_root;
    root = new_root;
    ++size_;
    SplitChild(new_root, 0, t_);
    ++size_;
  }
  int delta = 0;
  InsertNonfull(root, key, t_, delta);
  size_ += delta;
}

size_t BTree::size() const {
  if (size_ == 1 && root->key.empty()) {
    return 0;
  }
  return size_;
}

int64_t calc_sum(Node* node) {
  if (node->isLeaf) {
    int64_t sum = 0;
    for (auto key : node->key) {
      sum += key;
    }
    return sum;
  }

  int64_t sum = 0;
  for (auto child : node->children) {
    sum += calc_sum(child);
  }
  return sum;
}

int64_t BTree::sum() const {
  if (root == nullptr) {
    return 0;
  }
  return calc_sum(root);
}
/*
void print_helper(Node *node, std::vector<std::vector<int>> &a, Node *parent = nullptr, int depth = 0) {
  if (node != nullptr) {
    //std::cout << parent << ' ' << node << std::endl;
    //std::cout << "depth = " << depth << " address = " << &node << " parent = " << &parent << std::endl;
    std::cout << "depth = " << depth << ' ';
    std::cout << '(';
    for (auto el : node->key) {
      std::cout << el << ',';
      a[depth].push_back(el);
    }
    std::cout << ')' << std::endl;
    for (auto el : node->children) {
      print_helper(el,a, node, depth + 1);
    }
  }
}

void BTree::print() {
  std::vector<std::vector<int>> arr(100);
  print_helper(root, arr);
  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i].size() == 0) {
      break;
    }
  }
}*/