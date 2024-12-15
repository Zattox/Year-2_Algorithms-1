#include "btree.h"
#include <iostream>

Node::Node(int t) : parent(nullptr), isLeaf(false), t(t){
}

BTree::BTree(int t) : t_(t), size_(0){
  root = new Node(t);
  root->isLeaf = true;
}

BTree::~BTree(){

}

void SplitChild(Node *x, int t, int i) {
  Node *y = x->children[i];
  Node *z = new Node(t);
  z->isLeaf = y->isLeaf;

  for (int j = 0; j < t / 2 - 1;++j) {
    z->key[j] = y->key[j + t / 2];
  }

  if (!y->isLeaf) {
    for (int j = 0; j < t / 2; ++j) {
      z->children[j] = y->children[j + t / 2];
    }
  }

  for (int j = x->key.size() - 1; j >= i + 1; --j) {
    x->children[j + 1] = x->children[j];
  }
  x->children[i + 1] = z;

  for (int j = x->key.size() - 1; j >= i; --j) {
    x->key[j  + 1] = x->key[j];
  }

  x->key.push_back(y->key[t / 2 - 1]);
}

void InsertNonfull(Node* x, int key, int t) {
  int i = x->key.size() - 1;
  while (i >= 0 && key < x->key[i]) {
    --i;
  }
  ++i;
  if (x->isLeaf) {
    x->key.insert(x->key.begin() + i, key);
  } else {
    if (x->children[i]->key.size() == t - 1) {
      SplitChild(x, t, i);
      if (key > x->key[i]) {
        ++i;
      }
    }
    InsertNonfull(x->children[i], key, t);
  }
}

void BTree::insert(int key) {
  if (root->key.size() == 2 * t_ - 1) {
    auto old_root = root;
    auto node = new Node(t_);
    root = node;
    node->children.push_back(old_root);
    SplitChild(node, t_, 0);
    InsertNonfull(node, key, t_);
  } else {
    InsertNonfull(root, key, t_);
  }
}

size_t BTree::size() const {
  return size_;
}

int64_t calc_sum(Node* node) {
  if (node->isLeaf) {
    int64_t sum = 0;
    for (auto el : node->key) {
      sum += el;
    }
    return sum;
  }

  int64_t sum = 0;
  for (auto el  : node->children) {
    sum += calc_sum(el);
  }
  return sum;
}

int64_t BTree::sum() const {
  if (root == nullptr) {
    return 0;
  }
  int64_t ans = calc_sum(root);
  return ans;
}

void traverse(Node* x) {
  int i;
  for (i = 0; i < x->key.size(); i++) {
    if (!x->isLeaf)
      traverse(x->children[i]);
    std::cout << " " << x->key[i];
  }

  if (!x->isLeaf)
    traverse(x->children[i]);
}