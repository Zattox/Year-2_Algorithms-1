#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
};

inline bool cmp_x (const Point &p1, const Point &p2) {
  return p1.x < p2.x || p1.x == p2.x && p1.y < p2.y;
}

inline bool cmp_y (const Point &p1, const Point &p2) {
  return p1.y < p2.y;
}

double distance(Point &a, Point &b) {
  return hypot(a.x - b.x, a.y - b.y);
}

double naive(vector<Point> &arr, int l, int r) {
  double ans = 2e9;
  for (int i = l; i < r; ++i) {
    for (int j = i + 1; j < r; ++j) {
      ans = min(ans, distance(arr[i], arr[j]));
    }
  }
  sort(arr.begin() + l, arr.begin() + r, cmp_y);
  return ans;
}

void sort_closest(vector<Point> &arr, int l, int m, int r) {
  int sz_l = m - l, sz_r = r - m;
  vector<Point> half_l(sz_l), half_r(sz_r);
  copy(arr.begin() + l, arr.begin() + m, half_l.begin());
  copy(arr.begin() + m, arr.begin() + r, half_r.begin());

  int i = 0, j = 0;
  int cur = l;
  while (i < sz_l && j < sz_r) {
    if (cmp_y(half_l[i], half_r[j])) {
      arr[cur] = half_l[i];
      ++i;
    } else {
      arr[cur] = half_r[j];
      ++j;
    }
    ++cur;
  }

  while (i < sz_l) {
    arr[cur] = half_l[i];
    ++i;
    ++cur;
  }

  while (j < sz_r) {
    arr[cur] = half_r[j];
    ++j;
    ++cur;
  }
}

double find_min_dist(vector<Point> &arr, int l, int r) {
  if (r - l <= 4) {
    return naive(arr, l, r);
  }

  int m = (l + r) / 2;
  Point midPoint = arr[m];

  double dist_l = find_min_dist(arr, l, m);
  double dist_r = find_min_dist(arr, m, r);
  double min_dist = min(dist_l, dist_r);

  sort_closest(arr, l, m, r);

  vector<Point> closest;
  for (int i = l; i < r; ++i) {
    if (abs(arr[i].x - midPoint.x) < min_dist) {
      closest.push_back(arr[i]);
    }
  }

  for (int i = 0; i < closest.size(); ++i) {
    int j = i + 1;
    while (j < closest.size() && (closest[j].y - closest[i].y) < min_dist) {
      min_dist = min(min_dist, distance(closest[j], closest[i]));
      ++j;
    }
  }

  return min_dist;
}

void solve() {
  int x, y;
  vector<Point> arr;
  while (cin >> x >> y) {
    arr.push_back({x, y});
  }

  std::sort(arr.begin(), arr.end(), cmp_x);

  double ans = find_min_dist(arr, 0, arr.size());
  cout << (int)ans;
}

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  while (t > 0) {
    solve();
    --t;
  }
}