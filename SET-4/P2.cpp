#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

struct Node {
  int key = -1;
  int left = -1, right = -1;
  char color = 'B';
};

vector<Node> arr;

bool check_BST(int i, int min_key, int max_key) {
  if (i == -1)
    return true;
  if (!(min_key < arr[i].key && arr[i].key < max_key))
    return false;
  return check_BST(arr[i].left, min_key, arr[i].key)
      && check_BST(arr[i].right, arr[i].key, max_key);
}

pair<bool, int> check_RB(int i) {
  if (i == -1) {
    return {true, 0};
  }

  if (arr[i].color == 'R' && arr[i].left != -1 && arr[arr[i].left].color == 'R') {
    return {false, -1};
  }
  if (arr[i].color == 'R' && arr[i].right != -1 && arr[arr[i].right].color == 'R') {
    return {false, -1};
  }

  auto sum_l = check_RB(arr[i].left);
  auto sum_r = check_RB(arr[i].right);
  if (!sum_l.first || !sum_r.first || sum_l.second != sum_r.second) {
    return {false, -1};
  }

  pair<bool, int> cur_s = {true, sum_l.second};
  if (arr[i].color == 'B') {
    ++cur_s.second;
  }

  return cur_s;
}

void solve() {
  int n, root;
  cin >> n;
  if (n == 0) {
    cout << "NO";
    return;
  }

  cin >> root;
  arr.resize(n + 1);
  for (int i = 0; i < n; ++i) {
    int number;
    cin >> number;
    cin >> arr[number].key;
    string l, r;
    cin >> l >> r;
    if (l != "null")
      arr[number].left = atoi(l.c_str());
    if (r != "null")
      arr[number].right = atoi(r.c_str());
    cin >> arr[number].color;
  }

  if (!check_BST(root, -INF, INF)) {
    cout << "NO";
    return;
  }

  if (arr[root].color == 'B' && check_RB(root).first) {
    cout << "YES";
  } else {
    cout << "NO";
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
