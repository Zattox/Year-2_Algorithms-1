#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

int next_bit(pair<int, int> &num){
  int bit = num.first % 2;
  num.first = (num.first >> 1);
  return bit;
}

vector<int> radixSort(vector<int> &a) {
  int n = (int)a.size(), max_sz = 32;
  int cnt_negative = 0;
  vector<pair<int, int>> arr(n);
  for (int i = 0; i < n; ++i) {
    arr[i] = {a[i], i};
    if (a[i] < 0)
      ++cnt_negative;
  }

  int prev_half = n;
  vector<pair<int, int>> additional_arr(n);
  for (int ind = 0; ind < max_sz; ++ind) {
    int l = 0, r = n - 1;
    for (int i = 0; i < prev_half; ++i) {
      if (next_bit(arr[i]) == 0)
        additional_arr[l++] = arr[i];
      else
        additional_arr[r--] = arr[i];
    }
    for (int i = n - 1; i >= prev_half; --i) {
      if (next_bit(arr[i]) == 0)
        additional_arr[l++] = arr[i];
      else
        additional_arr[r--] = arr[i];
    }
    arr.swap(additional_arr);
    prev_half = l;
  }

  int ch = 0;
  vector<int> radix_ans(n);
  for (int i = 0; i < prev_half; ++i) {
    radix_ans[ch++] = a[arr[i].second];
  }
  for (int i = n - 1; i >= prev_half; --i) {
    radix_ans[ch++] = a[arr[i].second];
  }

  ch = 0;
  vector<int> ans(n);
  for (int i = n - cnt_negative; i < n; ++i) {
    ans[ch++] = radix_ans[i];
  }
  for (int i = 0; i < n - cnt_negative; ++i) {
    ans[ch++] = radix_ans[i];
  }

  return ans;
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  auto ans = radixSort(a);
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
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
