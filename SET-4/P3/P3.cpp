#include <bits/stdc++.h>
#include "release.cpp"

typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
  AVLTree T;
  for (int i = 0; i < 10; ++i) {
    cout << "Find " << i << " : " << T.find(i + 1) << "\n";
    T.insert(i + 1);
    cout << "Find " << i << " : " << T.find(i + 1) << "\n";
    cout << "--------------------------------------\n";
  }

  auto x = T.traversal();
  cout << "arr = ";
  for (int i = 0; i < 10; ++i) {
    cout << x[i] << ' ';
  }
  cout << "\n";

  cout << T.empty() << "\n";
  for (int i = 0; i < 11; ++i) {
    cout << "size = " << T.getSize() << " height = " << T.getHeight() << "\n";
    T.erase(i);
    cout << "size = " << T.getSize() << " height = " << T.getHeight() << "\n";
    cout << "============================================\n";
  }
  cout << T.empty() << "\n";

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
