#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve() {
  string pattern, text;
  cin >> pattern >> text;
  int m = pattern.size(), n = text.size();

  unordered_map<char, int> shift_table;
  for (int i = 0; i < m - 1; ++i) {
    shift_table[pattern[i]] = m - i - 1;
  }

  vector<int> arr;
  int i = 0;
  while (i <= n - m) {
    int j = m - 1;
    while (j >= 0 && text[i + j] == pattern[j]) {
      --j;
    }

    if (j == -1) {
      arr.push_back(i);
      ++i;
    } else {
      char mismatch_char = text[i + m - 1];
      int shift = shift_table.count(mismatch_char);
      if (shift == 0)
        shift = m;
      i += shift;
    }
  }

  cout << arr.size() << '\n';
  for (auto el : arr) {
    cout << el << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  //cin >> t;
  while (t > 0) {
    solve();
    --t;
  }
}