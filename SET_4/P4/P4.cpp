#include <bits/stdc++.h>
#include "rbtree.cpp"

typedef long long ll;
typedef long double ld;
using namespace std;

void print_tree_helper(Node* root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    }
    else {
      cout << "L----";
      indent += "|  ";
    }
    string sColor
        = (root->color == Color::RED) ? "RED" : "BLACK";
    cout << root->key << "(" << sColor << ")"
         << endl;
    print_tree_helper(root->left, indent, false);
    print_tree_helper(root->right, indent, true);
  }
}

void print_tree(Node* root){
  if (root == nullptr) {
    cout << "Tree is empty" << endl;
  } else {
    cout << "Heigth = " << getNodeHeight(root) << " Size = " << getNodeSize(root) << endl;
    cout << "Red-Black tree: " << endl;
    print_tree_helper(root, "", true);
    cout << endl;
  }
}

void test1(){
  initializer_list<int> list_1 = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6};
  RBTree rbtree(list_1);

  print_tree(rbtree.root);

  cout << "Find : " << rbtree.find(18) << endl;
  cout << "After deleting 18:" << endl;
  rbtree.erase(18);
  print_tree(rbtree.root);

  cout << "Find : " << rbtree.find(11) << endl;
  cout << "After deleting 11:" << endl;
  rbtree.erase(11);
  print_tree(rbtree.root);

  cout << "Find : " << rbtree.find(3) << endl;
  cout << "After deleting 3:" << endl;
  rbtree.erase(3);
  print_tree(rbtree.root);

  cout << "Find : " << rbtree.find(7) << endl;
  cout << "After deleting 7:" << endl;
  rbtree.erase(7);
  print_tree(rbtree.root);

  cout << "Find : " << rbtree.find(8) << endl;
  cout << "After deleting 8:" << endl;
  rbtree.erase(8);
  print_tree(rbtree.root);

  cout << "Find : " << rbtree.find(100) << endl;
  cout << "Find : " << rbtree.find(1200) << endl;
}

void test2(){
  RBTree tree;
  print_tree(tree.root);
  cout << tree.size() << ' ' << tree.height() << endl;
  tree.insert(1);
  tree.insert(1);
  print_tree(tree.root);
  tree.erase(1);
  tree.erase(1);
  print_tree(tree.root);
}

void solve() {
  test1()
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
