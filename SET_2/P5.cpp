#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
};

bool cmp_x(const Point &p1, const Point &p2) {
  if (p1.x == p2.x) {
    return p1.y < p2.y;
  }
  return p1.x < p2.x;
}

bool cmp_y(const Point &p1, const Point &p2) {
  if (p1.y == p2.y) {
    return p1.x < p2.x;
  }
  return p1.y < p2.y;
}

int dist(Point &a, Point &b) {
  return (int)hypot(a.x - b.x, a.y - b.y);
}

int naive_dist(vector<Point> &arr, int s, int f) {
  int ans = 2e9;
  for (int i = s; i < f; ++i) {
    for (int j = i + 1; j < f; ++j) {
      ans = min(ans, dist(arr[i], arr[j]));
    }
  }

  return ans;
}

int closest_dist(vector<Point> &arr, int d) {
  int ans = d;
  for (int i = 0; i < arr.size(); ++i) {
    int j = i + 1;
    while (j < arr.size() && (arr[j].y - arr[i].y) < ans) {
      ans = min(ans, dist(arr[i], arr[j]));
      ++j;
    }
  }
  return ans;
}

int find_min_dist(vector<Point> &arr,vector<Point> &closest_arr, int s, int f) {
  int n = f - s;
  if (n <= 1000) {
    return naive_dist(arr, s, f);
  }

  int mid = (s + f) / 2;
  Point midPoint = arr[mid];

  int dist_l = find_min_dist(arr, closest_arr, s, mid);
  int dist_r = find_min_dist(arr, closest_arr, mid, f);
  int d = min(dist_l, dist_r);

  vector<Point> closest_points;
  for (int i = 0; i < closest_arr.size(); ++i) {
    if (abs(closest_arr[i].x - midPoint.x) < d) {
      closest_points.push_back(closest_arr[i]);
    }
  }

  return min(d, closest_dist(closest_points, d));
}

void solve() {
  int x, y;
  vector<Point> arr;
  while (cin >> x >> y) {
    arr.push_back({x, y});
  }
  vector<Point> closest_arr = arr;

  std::sort(arr.begin(), arr.end(), cmp_x);
  std::sort(closest_arr.begin(), closest_arr.end(),cmp_y);
  double ans = find_min_dist(arr, closest_arr, 0, arr.size());
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
