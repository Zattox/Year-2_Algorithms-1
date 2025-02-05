#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  int n, k, last_n = 0, last_num = 1;
  vector<pair<int, int>> vec;
  vector<int> mas;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    mas.push_back(x);
    if (x == last_num) {
      k = 0;
      vec.push_back({1, (i - last_n) + 1});
      while ((last_num != n + 1) && (mas.back() == last_num)) {
        mas.pop_back();
        ++last_num;
        ++k;
      }
      last_n = i + 1;
      vec.push_back({2, k});
    }
  }
  if (last_num != n + 1) {
    cout << 0 << endl;
  } else {
    for (auto el : vec) {
      cout << el.first << ' ' << el.second << "\n";
    }
  }
}