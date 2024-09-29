#include <bits/stdc++.h>

using namespace std;

pair<int, int> searchKey(vector<vector<int>> &matrix, int n, int key) {
  int row = 0, col = 0;
  while (row < n && col < n) {
    if (matrix[row][col] == key) {
      return {row, col};
    } else if (matrix[row][col] > key) {
      ++row;
    } else {
      ++col;
    }
  }
  return {-1, -1};
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> matrix(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> matrix[i][j];
    }
  }
  int q;
  cin >> q;
  while (q > 0) {
    int key;
    cin >> key;
    auto ans = searchKey(matrix, n, key);
    cout << ans.first << ' ' << ans.second << endl;
    --q;
  }
}