#include <bits/stdc++.h>

using namespace std;

string unpacking(string &str, int &i) {
  string result;
  int count = 0;
  while (i < (int) str.size()) {
    if (isdigit(str[i])) {
      count = str[i] - '0';
    } else if (str[i] == '[') {
      i += 1;
      string substr = unpacking(str, i);
      for (int j = 0; j < count; ++j) {
        result += substr;
      }
    } else if (str[i] == ']') {
      return result;
    } else {
      result += str[i];
    }
    ++i;
  }

  return result;
}

void solve() {
  string str;
  getline(cin, str);

  int start = 0;
  string ans = unpacking(str, start);
  cout << ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();

  return 0;
}
