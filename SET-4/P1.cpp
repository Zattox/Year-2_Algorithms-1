#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
  Node *left, *right;
  int value;
  int sz = 0;
} * tree;

int GetSize(Node* T) {
  if (T == nullptr) {
    return 0;
  }
  return T->sz;
}

Node* NewNode(int x) {
  return new Node{nullptr, nullptr, x,1 };
}

void recalc(Node* T) {
  if (T != nullptr) {
    T->sz = max(GetSize(T->left), GetSize(T->right)) + 1;
  }
}

void insert(tree &T, int x) {
  if (x < T->value) {
    if (T->left == nullptr) {
      T->left = NewNode(x);
    } else {
      insert(T->left, x);
    }
  } else {
    if (T->right == nullptr) {
      T->right = NewNode(x);
    } else {
      insert(T->right, x);
    }
  }
  recalc(T);
}

bool CheckAVL(tree T) {
  if (T == nullptr) {
    return true;
  }
  int sz_l = GetSize(T->left);
  int sz_r = GetSize(T->right);
  if (abs(sz_l - sz_r) > 1) {
    return false;
  }
  return (CheckAVL(T->left) && CheckAVL(T->right));
}

void print_tree(tree T) {
  if (T != nullptr) {
    cout << T->value << ' ';
    print_tree(T->left);
    print_tree(T->right);
  }
}

void solve() {
  int x;
  cin >> x;
  tree BinaryTree = NewNode(x);
  while (cin >> x) {
    if (x == 0) {
      break;
    }
    insert(BinaryTree, x);
  }

  //print_tree(BinaryTree);

  if (CheckAVL(BinaryTree)) {
    cout << "\nYES";
  } else {
    cout << "\nNO";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  // cin >> t;
  while (t > 0) {
    solve();
    --t;
  }
}
