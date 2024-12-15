#include <bits/stdc++.h>
#include "btree.cpp"

typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
  BTree t(3);
  t.insert(10);
  t.insert(20);
  t.insert(5);
  t.insert(6);
  t.insert(12);
  t.insert(30);
  t.insert(7);
  t.insert(17);
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
