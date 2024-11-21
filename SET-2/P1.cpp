#include <bits/stdc++.h>

using namespace std;

struct Interval {
  int left;
  int right;

  size_t length() {
    if (left > right) {
      return 0;
    }
    return right - left + 1;
  }

  Interval overlap(const Interval& other) {
    if (other.left > right || left > other.right) {
      return {1, 0};
    }
    return {max(left, other.left), min(right, other.right)};
  }

};

bool comparison(Interval &a, Interval &b) {
  if (a.left == b.left) {
    return a.right < b.right;
  }
  return a.left < b.left;
}

vector<Interval> mergesort(int l, int r, vector<Interval> &arr) {
  if (r - l <= 0) {
    return {};
  } else if (r - l == 1) {
    return {arr[l]};
  }

  int m = (l + r) / 2;
  vector<Interval> left_half = mergesort(l, m, arr);
  vector<Interval> right_half = mergesort(m, r, arr);
  vector<Interval> result;

  int i = 0, j = 0;
  while (i < left_half.size() || j < right_half.size()) {
    if (i == left_half.size()) {
      result.push_back(right_half[j]);
      ++j;
    } else if (j == right_half.size()) {
      result.push_back(left_half[i]);
      ++i;
    } else {
      if (comparison(left_half[i], right_half[j])) {
        result.push_back(left_half[i]);
        ++i;
      } else {
        result.push_back(right_half[j]);
        ++j;
      }
    }
  }

  return result;
}

void solve() {
  int n;
  cin >> n;
  if (n == 0) {
    cout << 0;
    return;
  }

  vector<Interval> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i].left >> arr[i].right;
  }

  vector<Interval> sort_arr = mergesort(0, n, arr);

  Interval ans = {0, -1};
  Interval curr = sort_arr[0];
  for (int i = 1; i < n; ++i) {
    Interval intersection = curr.overlap(sort_arr[i]);
    if (intersection.length() > ans.length()) {
      ans = intersection;
    }
    if (sort_arr[i].right > curr.right) {
      curr = sort_arr[i];
    }
  }

  if (ans.length() > 0) {
    cout << ans.length() << "\n";
    cout << ans.left << ' ' << ans.right;
  } else {
    cout << 0;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  while (t > 0) {
    solve();
    --t;
  }
}