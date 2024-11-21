#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

void heap_construction(vector<int> &arr, int n, int ind) {
  int biggest = ind;
  int left_child = 2 * ind + 1;
  int right_child = 2 * ind + 2;

  if (left_child < n && arr[left_child] > arr[biggest]) {
    biggest = left_child;
  }
  if (right_child < n && arr[right_child] > arr[biggest]) {
    biggest = right_child;
  }

  if (biggest != ind) {
    swap(arr[biggest], arr[ind]);
    heap_construction(arr, n, biggest);
  }
}

void heap_sort(vector<int> &arr, int n) {
  for (int i = n / 2 - 1; i >= 0; --i) {
    heap_construction(arr, n, i);
  }

  for (int i = n - 1; i > 0; --i) {
    swap(arr[0], arr[i]);
    heap_construction(arr, i, 0);
  }
}

void solve() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  heap_sort(arr, n);

  for (auto el : arr) {
    cout << el << ' ';
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
