#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

size_t getHash(string key, int p) {
  ll h = 0, powOfP = 1;
  for (int i = 0; i < key.size(); ++i) {
    h += (key[i] - 'a' + 1) * powOfP;
    powOfP *= p;
  }
  return h;
}

vector<char> dict;
vector<string> solve(int p) {
  vector<string> ans;
  for (auto firstEl : dict) {
    for (auto secondEl : dict) {
      string cur;
      cur += firstEl;
      cur += secondEl;
      if (getHash(cur, p) == 0) {
        ans.push_back(cur);
      }
    }
  }
  return ans;
}

int main() {
  freopen("result.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  for (char sym = 'a'; sym <= 'z'; ++sym) {
    dict.push_back(sym);
  }
  for (char sym = 'A'; sym <= 'Z'; ++sym) {
    dict.push_back(sym);
  }
  for (char sym = '0'; sym <= '9'; ++sym) {
    dict.push_back(sym);
  }

  for (int p = 1; p <= 31; ++p) {
    cout << "p = " << p << "\n";
    auto ans = solve(p);
    cout << "The neutral elems: ";
    for (auto &el : ans) {
      cout << el << ' ';
    }
    cout << endl;
  }
}