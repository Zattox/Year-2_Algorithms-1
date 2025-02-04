#include <bits/stdc++.h>
#include "btree.cpp"

typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
  BTree t(2);
  vector<int> x = {10, 20, 35, 40, 50, 65, 70, 80, 90, 100, 110, 120, 130, 140, 160, 180, 190, 240, 260};
  //vector<double> x = {2, 5, -1, 4, -5, 6, 7, 3, 3.7, 3.5};
  //vector<int> x = {2, 5, -1, 4, 3, 3, 3};
  cout << t.sum() << ' ';
  cout << t.size() << endl;
  for (auto el : x) {
    /*if (el == 40 || el == 65 || el == 100 || el == 260) {
      cout << "Do el = " << el << ":\n=================================" << endl;
      t.print();
      cout << "=================================" << endl;
    }*/
    t.insert(el);
    //if (el == 40 || el == 65 || el == 100 || el == 260) {
      //cout << "Posle el = " << el << ":\n=================================" << endl;
      t.print();
      cout << "=================================" << endl;
    //}
  }

  cout << t.sum() << ' ';
  cout << t.size() << endl;
  //t.print();
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
