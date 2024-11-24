#include <bits/stdc++.h>

using namespace std;

struct Circle {
  double x, y, r;
};

void solve() {
  double sq = 0.25 * M_PI + 1.25 * asin(0.8) - 1;
  cout.precision(20);
  cout << sq;
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