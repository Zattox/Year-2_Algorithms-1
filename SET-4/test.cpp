#include <iostream>
#include <initializer_list>

using namespace std;

enum class Color { RED, BLACK };

struct Node {
  int key;
  int height;
  int size;
  Node* left;
  Node* right;
  Node* parent;
  Color color;

  explicit Node(int key_) {
    key = key_;
    height = 1;
    size = 1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = Color::RED;
  }
};

class RBTree {
 public:
  Node* root;

  RBTree() {
    root = nullptr;
  }

  RBTree(std::initializer_list<int> list) {
    root = nullptr;
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

  ~RBTree() {
    clear(root);
  }

  int getNodeSize(Node* node) {
    return node ? node->size : 0;
  }

  void fixSize(Node* node) {
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

  int* find(int key) {
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

  void leftRotate(Node*& node) {
    Node* tmp_r = node->right;
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

  void rightRotate(Node*& node) {
    Node* tmp_l = node->left;
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

  void fixInsert(Node* node) {
    while (node != root && node->parent != nullptr && node->parent->color == Color::RED) {
      Node* uncle = nullptr;
      if (node->parent == node->parent->parent->left) {
        uncle = node->parent->parent->right;
        if (uncle != nullptr && uncle->color == Color::RED) {
          node->parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          node = node->parent->parent; // поднимаемся на уровень выше
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            leftRotate(node);
          }
          node->parent->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          rightRotate(node->parent->parent);
        }
      } else {
        uncle = node->parent->parent->left;
        if (uncle != nullptr && uncle->color == Color::RED) {
          node->parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          node = node->parent->parent; // поднимаемся на уровень выше
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            rightRotate(node);
          }
          node->parent->color = Color::BLACK;
          node->parent->parent->color = Color::RED;
          leftRotate(node->parent->parent);
        }
      }
    }
    root->color = Color::BLACK;
  }

  void insert(int key) {
    if (find(key) != nullptr) {
      return; // Не добавляем дубликаты
    }
    Node* newNode = new Node(key);
    if (root == nullptr) {
      root = newNode;
      root->color = Color::BLACK;
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

    if (key < prev->key) {
      prev->left = newNode;
    } else {
      prev->right = newNode;
    }
    newNode->parent = prev;
    fixInsert(newNode);
    fixHeight(root);
    fixSize(root);
  }

  int height() const {
    return root ? root->height : 0;
  }

  int size() const {
    return root ? root->size : 0;
  }

  int* lowerBound(int key) {
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

  bool empty() const {
    return size() == 0;
  }
};

void helper(Node* node) {
  if (node != nullptr) {
    helper(node->left);
    cout << node->key << ' ';
    helper(node->right);
  }
}

void print_tree(RBTree& rbtree) {
  helper(rbtree.root);
  cout << endl;
}

bool check_BST(Node* cur, int min_key, int max_key) {
  if (cur == nullptr)
    return true;
  if (!(min_key < cur->key && cur->key < max_key))
    return false;
  return check_BST(cur->left, min_key, cur->key)
      && check_BST(cur->right, cur->key, max_key);
}

pair<bool, int> check_RB(Node* cur) {
  if (cur == nullptr) {
    return { true, 0 };
  }

  if (cur->color == Color::RED && cur->left != nullptr && cur->left->color == Color::RED) {
    return { false, -1 };
  }
  if (cur->color == Color::RED && cur->right != nullptr && cur->right->color == Color::RED) {
    return { false, -1 };
  }

  auto sum_l = check_RB(cur->left);
  auto sum_r = check_RB(cur->right);
  if (!sum_l.first || !sum_r.first || sum_l.second != sum_r.second) {
    return { false, -1 };
  }

  pair<bool, int> cur_s = { true, sum_l.second };
  if (cur->color == Color::BLACK) {
    ++cur_s.second;
  }

  return cur_s;
}

void check(RBTree& rbtree) {
  int INF = 2e9;

  if (!check_BST(rbtree.root, -INF, INF)) {
    cout << "1. NO\n";
    return;
  }
  if (rbtree.root->color == Color::BLACK && check_RB(rbtree.root).first) {
    cout << "2. YES\n";
  } else {
    cout << "3. NO\n";
  }
}

void test1() {
  initializer_list<int> list_1 = { 7, 3, 18 };
  RBTree rbtree(list_1);

  print_tree(rbtree);
  check(rbtree);
  print_tree(rbtree);

  cout << "Find : " << rbtree.find(18) << endl;
  cout << "After deleting 18:" << endl;
  rbtree.erase(18);
  check(rbtree);
  print_tree(rbtree);

  cout << "Find : " << rbtree.find(11) << endl;
  cout << "After deleting 11:" << endl;
  rbtree.erase(11);
  check(rbtree);
  print_tree(rbtree);

  cout << "Find : " << rbtree.find(3) << endl;
  cout << "After deleting 3:" << endl;
  rbtree.erase(3);
  check(rbtree);
  print_tree(rbtree);

  cout << "Find : " << rbtree.find(100) << endl;
  cout << "Find : " << rbtree.find(1200) << endl;
}

void test2() {
  RBTree tree;
  print_tree(tree);
  std::cout << tree.size() << ' ' << tree.height() << endl;
  tree.insert(1);
  tree.insert(1);
  print_tree(tree);
  tree.erase(1);
  tree.erase(1);
  std::cout << "Find : " << tree.find(1) << std::endl;
  std::cout << "After deleting 1:" << std::endl;
  print_tree(tree);
}

int main() {
  test1();
  return 0;
}
