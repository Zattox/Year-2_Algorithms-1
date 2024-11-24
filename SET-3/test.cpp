#include <bits/stdc++.h>

using namespace std;

void insertionSort(vector<int> &arr) {
  int n = arr.size();
  for (int i = 1; i < n; ++i) {
    int elem = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > elem) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = elem;
  }
}

void solve() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    int el;
    cin >> el;
    arr[i] = el;
  }

  auto start_time = std::chrono::steady_clock::now();
  insertionSort(arr);
  auto end_time = std::chrono::steady_clock::now();
  auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  long double res = elapsed_ns.count() / 1000.0;
  cout.precision(10);
  cout << fixed << res << "\n";
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
