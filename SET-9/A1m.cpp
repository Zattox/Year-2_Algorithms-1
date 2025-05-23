#include <bits/stdc++.h>

using namespace std;

struct ComparisonResult {
  int result;
  size_t lcp;
};

ComparisonResult lcpCompare(const string &a, const string &b, size_t k = 0) {
  ComparisonResult result;
  result.lcp = k;

  while (k < a.length() && k < b.length() && a[k] == b[k]) {
    ++k;
  }

  result.lcp = k;

  if (k >= a.length() || k >= b.length()) {
    result.result = (a.length() == b.length()) ? 0 : (a.length() < b.length() ? -1 : 1);
  } else {
    result.result = (a[k] < b[k]) ? -1 : 1;
  }

  return result;
}

pair<vector<string>, vector<size_t>> merge(
    const vector<string> &left, const vector<size_t> &lcp_left,
    const vector<string> &right, const vector<size_t> &lcp_right) {

  vector<string> result;
  vector<size_t> lcp_result;
  size_t i = 0, j = 0;

  while (i < left.size() && j < right.size()) {
    ComparisonResult comp = lcpCompare(left[i], right[j]);

    if (comp.result <= 0) {
      result.push_back(left[i++]);
    } else {
      result.push_back(right[j++]);
    }

    if (result.size() > 1) {
      ComparisonResult lcp = lcpCompare(result[result.size() - 2], result[result.size() - 1]);
      lcp_result.push_back(lcp.lcp);
    }
  }

  while (i < left.size()) {
    result.push_back(left[i++]);
    if (result.size() > 1) {
      ComparisonResult lcp = lcpCompare(result[result.size() - 2], result[result.size() - 1]);
      lcp_result.push_back(lcp.lcp);
    }
  }

  while (j < right.size()) {
    result.push_back(right[j++]);
    if (result.size() > 1) {
      ComparisonResult lcp = lcpCompare(result[result.size() - 2], result[result.size() - 1]);
      lcp_result.push_back(lcp.lcp);
    }
  }

  return {result, lcp_result};
}

pair<vector<string>, vector<size_t>> mergeSort(const vector<string> &arr) {
  if (arr.size() <= 1) {
    return {arr, {}};
  }

  size_t mid = arr.size() / 2;
  vector<string> left(arr.begin(), arr.begin() + mid);
  vector<string> right(arr.begin() + mid, arr.end());

  auto [sorted_left, lcp_left] = mergeSort(left);
  auto [sorted_right, lcp_right] = mergeSort(right);

  return merge(sorted_left, lcp_left, sorted_right, lcp_right);
}

void solve() {
  string n_str;
  getline(cin, n_str);
  int n = atoi(n_str.c_str());

  vector<string> arr(n);
  for (int i = 0; i < n; ++i) {
    getline(cin, arr[i]);
  }

  auto [sorted_arr, lcp_arr] = mergeSort(arr);

  for (auto &el : sorted_arr) {
    cout << el << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}