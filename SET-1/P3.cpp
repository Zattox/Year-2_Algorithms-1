#include <bits/stdc++.h>

using namespace std;

void solve() {
  string str, ans;
  cin >> str;

  vector<int> st;
  for (int i = 0; i < (int)str.size(); ++i) {
    if (str[i] == '[') {
      st.push_back(i);
    } else if (str[i] == ']') {
      int ind = st.back();
      st.pop_back();
      string substr = str.substr(ind + 1, i - ind);
      
    }
  }

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  while (t > 0) {
    solve();
    --t;
  }

  return 0;
}
