#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

pair<int, int> frac_to_pair(string x) {
  int i = 0;
  string numerator;
  while (x[i] != '/') {
    numerator += x[i];
    ++i;
  }
  ++i;
  string denominator;
  while (i < x.size()){
    denominator += x[i];
    ++i;
  }
  return {atoi(numerator.c_str()), atoi(denominator.c_str())};
}

bool cmp(pair<int, int> p1, pair<int, int> p2) {
  ll x1 = 1ll * p1.first * p2.second;
  ll x2 = 1ll * p2.first * p1.second;

  return x1 < x2;
}

void solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> arr(n);
  for (int i = 0; i < n; ++i) {
    string x;
    cin >> x;
    arr[i] = frac_to_pair(x);
  }

  std::stable_sort(arr.begin(), arr.end(), cmp);

  for (auto el : arr) {
    cout << el.first << '/' << el.second << ' ';
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
