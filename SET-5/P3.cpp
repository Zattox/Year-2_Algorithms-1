#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

mt19937_64 rnd(time(NULL));

void initRandHash(vector<ll> &hash) {
  int sz = 1e6;
  hash.resize(sz);
  for (int i = 0; i <= sz; ++i) {
    hash[i] = rnd();
  }
}

pair<int, int> check(int len, vector<int> &a, vector<int> &b, vector<ll> &hash) {
  ll sumA = 0;
  for (int i = 0; i < a.size(); ++i) {
    sumA += hash[a[i]];
    if (i >= len) {
      sumA -= hash[a[i - len]];
    }
    if (i >= len - 1) {
      ll sumB = 0;
      for (int j = 0; j < b.size(); ++j) {
        sumB += hash[b[j]];
        if (j >= len) {
          sumB -= hash[b[j - len]];
        }
        if (j >= len - 1) {
          if (sumA == sumB) {
            return {i - len + 2, j - len + 2};
          }
        }
      }
    }
  }
  return {-1, -1};
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int m;
  cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }

  vector<ll> hash;
  initRandHash(hash);

  pair<int, int> ans = {-1, -1};
  int left = 0, right = min(n, m) + 1;
  while (left + 1 < right) {
    int mid = (left + right) / 2;
    auto cur_ans = check(mid, a, b, hash);
    if (cur_ans.first != -1) {
      left = mid;
      ans = cur_ans;
    } else {
      right = mid;
    }
  }

  cout << left << ' ' << ans.first << ' ' << ans.second;
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