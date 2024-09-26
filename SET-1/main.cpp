#include <bits/stdc++.h>

using namespace std;

int slow_solve(int n, vector<int> arr) {
  vector<vector<int>> all;
  for (int i = 1; i < n; ++i) {
    vector<int> a;
    for (int j = n - i; j < n; ++j) {
      a.push_back(arr[j]);
    }
    for (int j = 0; j < n - i; ++j) {
      a.push_back(arr[j]);
    }
    all.push_back(a);
  }

  vector<int> scores;
  int max_score = 0;
  for (auto a : all) {
    int score = 0;
    for (int i = 0; i < n; ++i) {
      if (arr[i] != a[i]) {
        ++score;
      }
    }
    max_score = max(max_score, score);
    scores.push_back(score);
  }

  int ans = 0;
  for (auto el : scores) {
    if (el == max_score) {
      ++ans;
    }
  }
  return ans;
}

int solve(int n, vector<int> arr) {
  vector<int> scores;

  int max_score = 0;
  for (int i = 1; i < n; ++i) {
    int score = 0;
    for (int j = 0; j < n; ++j) {
      if (arr[j] != arr[(i + j) % n]){
        ++score;
      }
    }
    max_score = max(score, max_score);
    scores.push_back(score);
  }

  int ans = 0;
  for (auto sc : scores) {
    if (sc == max_score) {
      ++ans;
    }
  }

  return ans;
}



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  for (int n = 1; n <= 10; ++n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
      arr[i] = rand();
    }
    auto sl = solve(n, arr);
    auto slow_sl = slow_solve(n, arr);
    if (sl != slow_sl) {
      cout << n << "\n";
      for (auto el : arr) {
        cout << el << ' ';
      }
      cout << "\nbad: " << sl;
      cout << "\ngood: " << slow_sl;
      cout << "\n";
    }
  }

  return 0;
}
