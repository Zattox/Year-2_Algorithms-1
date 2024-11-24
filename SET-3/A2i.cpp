#include <bits/stdc++.h>

using namespace std;

void insertionSort(vector<int> &arr, int l, int r) {
  for (int i = l + 1; i <= r; ++i) {
    int elem = arr[i];
    int j = i - 1;
    while (j >= l && arr[j] > elem) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = elem;
  }
}

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

  while(i < sz_l) {
    arr[cur++] = half_l[i++];
  }
  while(j < sz_r) {
    arr[cur++] = half_r[j++];
  }
}

void mergeSortHybrid(vector<int>& arr, int left, int right) {
  if (right - left <= 15) {
    insertionSort(arr, left, right);
  } else {
    int mid = left + (right - left) / 2;
    mergeSortHybrid(arr, left, mid);
    mergeSortHybrid(arr, mid + 1, right);
    merge(arr, left, mid, right);
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
  mergeSortHybrid(arr, 0, arr.size() - 1);
  for (auto el : arr) {
    cout << el << " ";
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
