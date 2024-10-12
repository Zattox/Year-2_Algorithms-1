#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

struct Point {
  int x, y, z;
};

double dist(Point &a, Point &b) {
  return hypot(a.x - b.x, a.y - b.y, a.z - b.z);
}

void naive_dist(vector<Point> &arr) {
  double ans = 2e9;
  int ind1 = 0, ind2 = 0;
  for (int i = 0; i < arr.size(); ++i) {
    for (int j = i + 1; j < arr.size(); ++j) {
      double d = dist(arr[i], arr[j]);
      if (ans > d) {
        ans = d;
        ind1 = i;
        ind2 = j;
      }
    }
  }

  cout.precision(20);
  cout << ans << "\n";
  cout << ind1 + 1 << ' ' << ind2 + 1;
}

void solve() {
  int n;
  cin >> n;
  vector<Point> arr(n);
  for(int i = 0; i < n; ++i) {
    cin >> arr[i].x >> arr[i].y >> arr[i].z;
  }

  naive_dist(arr);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  while (t > 0) {
    solve();
    --t;
  }
}
