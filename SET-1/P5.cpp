#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n;
  cin >> n;

  deque<int> start, middle;
  char command;
  for (int i = 0; i < n; ++i) {
    cin >> command;
    if (command == '-') {
      cout << start.front() << "\n";
      start.pop_front();
    } else if (command == '+') {
      int number;
      cin >> number;
      middle.push_back(number);
    } else {
      int number;
      cin >> number;
      middle.push_front(number);
    }
    if (start.size() < middle.size()) {
      start.push_back(middle.front());
      middle.pop_front();
    }
  }

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  while (t > 0) {
    solve();
    --t;
  }

  return 0;
}
