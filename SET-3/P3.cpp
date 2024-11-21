#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

string dec_to_bin(int x) {
  string ans;
  while (x > 0) {
    ans.push_back('0' + x % 2);
    x /= 2;
  }
  std::reverse(ans.begin(), ans.end());
  return ans;
}

int bin_to_dec(string x) {
  std::reverse(x.begin(), x.end());
  int ans = 0;
  int k = 1;
  for (auto el : x) {
    ans += (el - '0') * k;
    k = (k << 1);
  }
  return ans;
}

void filling_zeros(string &x, int n) {
  std::reverse(x.begin(), x.end());
  while (x.size() < n) {
    x.push_back('0');
  }
  std::reverse(x.begin(), x.end());
}

int sort_by_digit(vector<string> &arr, int ind, int prev_half) {
  vector<string> additional_arr(arr.size());
  int l = 0, r = (int)arr.size() - 1;

  for (int i = 0; i < prev_half; ++i) {
    auto el = arr[i];
    if (el[ind] == '0') {
      additional_arr[l++] = el;
    } else {
      additional_arr[r--] = el;
    }
  }

  for (int i = (int)arr.size() - 1; i >= prev_half; --i) {
    auto el = arr[i];
    if (el[ind] == '0') {
      additional_arr[l++] = el;
    } else {
      additional_arr[r--] = el;
    }
  }

  arr.swap(additional_arr);
  return l;
}

vector<int> radixSort(vector<int> &a) {
  int n = (int)a.size(), max_sz = 0;
  vector<string> binary_a(n);
  for (int i = 0; i < n; ++i) {
    binary_a[i] = dec_to_bin(a[i]);
    max_sz = max(max_sz, (int)binary_a[i].size());
  }
  for (int i = 0; i < n; ++i) {
    filling_zeros(binary_a[i], max_sz);
  }

  int half = n;
  for (int i = max_sz - 1; i >= 0; --i) {
    half = sort_by_digit(binary_a, i, half);
  }

  int ch = 0;
  vector<int> ans(n);
  for (int i = 0; i < half; ++i) {
    ans[ch++] = bin_to_dec(binary_a[i]);
  }
  for (int i = n - 1; i >= half; --i) {
    ans[ch++] = bin_to_dec(binary_a[i]);
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
