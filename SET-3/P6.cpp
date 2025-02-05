#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int count_queens(vector<int> &arr) {
  size_t n = arr.size();
  vector<bool> diag_sum(2 * n - 1), diag_diff(2 * n - 1);
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    int sum = i + arr[i];
    int diff = i - arr[i] + (n - 1);
    if (!diag_sum[sum] && !diag_diff[diff]) {
      cnt++;
      diag_sum[sum] = true;
      diag_diff[diff] = true;
    }
  }
  return cnt;
}

void solve() {
  int n;
  cin >> n;
  std::mt19937 generator(13);
  std::uniform_int_distribution<> distr(0, n - 1);
  std::uniform_real_distribution<> real_distr(0, n - 1);

  vector<int> spots(n);
  for (int i = 0; i < n; ++i) {
    spots[i] = i;
  }
  shuffle(spots.begin(), spots.end(), generator);

  double Ti = 1.0;
  int cur_cnt = count_queens(spots);
  while (cur_cnt < n) {
    Ti *= 0.99;
    vector<int> newSpots = spots;
    swap(newSpots[distr(generator)], newSpots[distr(generator)]);

    int new_cnt = count_queens(newSpots);
    int diffrence = new_cnt - cur_cnt;
    if (new_cnt > cur_cnt || real_distr(generator) < exp(diffrence / Ti)) {
      spots = newSpots;
      cur_cnt = new_cnt;
    }
  }

  for (auto el : spots) {
    cout << el + 1 << ' ';
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
