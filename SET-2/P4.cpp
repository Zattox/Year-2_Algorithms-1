#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

ld find_dist(vector<pair<ll, ll>> &arr, ld time) {
  ld dist = 0, cur_time = 0;
  int i = 0;
  while (i < arr.size()) {
    if (cur_time + arr[i].first <= time) {
      dist += arr[i].first * arr[i].second;
      cur_time += arr[i].first;
    } else {
      break;
    }
    ++i;
  }
  if (cur_time < time) {
    dist += (time - cur_time) * arr[i].second;
  }
  return dist;
}

bool check(vector<pair<ll,ll>> &arr, ll len, ld time) {
  if (find_dist(arr, time) < len) {
    return false;
  }

  ld dist_first = 0, time_first = 0;
  ld dist_second = 0, time_second = 0;
  for (int i = 0; i < arr.size(); ++i) {
    time_first += arr[i].first;
    dist_first += arr[i].first * arr[i].second;
    if (time_first < time) {
      continue;
    }
    time_second = time_first;
    dist_second = find_dist(arr, time_second - time);
    if (dist_first - dist_second < len) {
      return false;
    }
  }

  return true;
}

void solve() {
  int len, n;
  cin >> len >> n;
  vector<pair<ll, ll>> info(n);
  for (int i = 0; i < n; ++i) {
    cin >> info[i].first >> info[i].second;
  }

  ld l = 0, r = 2e9;
  for (int i = 0; i < 64; ++i) {
    ld m = (l + r) / 2.0;
    if (check(info, len, m)) {
      r = m;
    } else {
      l = m;
    }
  }

  cout.precision(20);
  cout << r;
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