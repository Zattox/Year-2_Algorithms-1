#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x, y;
};

struct Circle {
  double x, y, r, r2;
};

bool in_circle(Point p, Circle c) {
  double dx = (p.x - c.x) * (p.x - c.x);
  double dy = (p.y - c.y) * (p.y - c.y);
  return (dx + dy) <= c.r2;
}

void solve() {
  Circle c1, c2, c3;
  cin >> c1.x >> c1.y >> c1.r;
  cin >> c2.x >> c2.y >> c2.r;
  cin >> c3.x >> c3.y >> c3.r;
  int cnt_points;
  cin >> cnt_points;

  c1.r2 = c1.r * c1.r;
  c2.r2 = c2.r * c2.r;
  c3.r2 = c3.r * c3.r;

  double max_x = max({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
  double min_x = max({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
  double max_y = min({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});
  double min_y = min({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
  double area = (max_x - min_x) * (max_y - min_y);

  std::mt19937 generator(13);
  std::uniform_real_distribution<> distr_x(min_x, max_x);
  std::uniform_real_distribution<> distr_y(min_y, max_y);

  double cnt_good = 0;
  for (int i = 0; i < cnt_points; ++i) {
    double cur_x = distr_x(generator);
    double cur_y = distr_y(generator);
    Point p = {cur_x, cur_y};
    if (in_circle(p, c1) && in_circle(p, c2) && in_circle(p, c3)) {
      cnt_good += 1;
    }
  }

  cout.precision(20);
  cout << area * cnt_good / cnt_points;
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