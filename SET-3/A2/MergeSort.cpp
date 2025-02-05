#include <bits/stdc++.h>

using namespace std;

void merge(vector<int> &arr, int l, int m, int r) {
  int sz_l = m - l + 1, sz_r = r - m;
  vector<int> half_l(sz_l), half_r(sz_r);
  for (int i = 0; i < sz_l; ++i) {
    half_l[i] = arr[l + i];
  }
  for (int i = 0; i < sz_r; ++i) {
    half_r[i] = arr[m + 1 + i];
  }

  int i = 0, j = 0, cur = l;
  while (i < sz_l && j < sz_r) {
    if (half_l[i] <= half_r[j]) {
      arr[cur++] = half_l[i++];
    } else {
      arr[cur++] = half_r[j++];
    }
  }

  while (i < sz_l) {
    arr[cur++] = half_l[i++];
  }
  while (j < sz_r) {
    arr[cur++] = half_r[j++];
  }
}

void mergeSort(vector<int> &arr, int l, int r) {
  if (l < r) {
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
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
  mergeSort(arr, 0, arr.size() - 1);
  auto end_time = std::chrono::steady_clock::now();
  auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
  long double res = elapsed_ns.count() / 1000;
  cout.precision(20);
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
