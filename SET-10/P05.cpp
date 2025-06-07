#include <bits/stdc++.h>

using namespace std;

struct Interval {
  double start_time, end_time, value;

  Interval(double start, double end, double val)
      : start_time(start), end_time(end), value(val) {}
};

bool compareByEndTime(const Interval &first, const Interval &second) {
  return first.end_time < second.end_time;
}

int findPreviousNonOverlapping(const vector<Interval> &intervals, int current_index) {
  int left = 0, right = current_index - 1;
  int best_index = -1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (intervals[mid].end_time <= intervals[current_index].start_time) {
      best_index = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return best_index;
}

void solve() {
  int n;
  cin >> n;

  if (n == 0) {
    cout << "0" << endl;
    return;
  }

  vector<Interval> intervals;
  for (int i = 0; i < n; i++) {
    double start, end, val;
    cin >> start >> end >> val;
    intervals.push_back(Interval(start, end, val));
  }

  sort(intervals.begin(), intervals.end(), compareByEndTime);

  vector<double> max_value(n + 1, 0.0);
  for (int i = 1; i <= n; i++) {
    double skip_cur = max_value[i - 1];
    int prev = findPreviousNonOverlapping(intervals, i - 1);
    double take_cur = intervals[i - 1].value;
    if (prev != -1) {
      take_cur += max_value[prev + 1];
    }
    max_value[i] = max(skip_cur, take_cur);
  }
  cout << fixed << setprecision(4) << max_value[n];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}