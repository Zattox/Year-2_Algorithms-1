#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

struct Item {
  ll value;
  ll weight;
  double ratio;
};

void solve() {
  int n;
  ll W;
  cin >> n >> W;

  vector<Item> items(n);
  for (int i = 0; i < n; i++) {
    cin >> items[i].value >> items[i].weight;
    items[i].ratio = (double) items[i].value / (double) items[i].weight;
  }

  sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
    return a.ratio > b.ratio;
  });

  ld total_value = 0.0;
  ll remaining = W;

  for (int i = 0; i < n && remaining > 0; i++) {
    if (items[i].weight <= remaining) {
      total_value += items[i].value;
      remaining -= items[i].weight;
    } else {
      double fraction = (double) remaining / (double) items[i].weight;
      total_value += items[i].value * fraction;
      remaining = 0;
    }
  }

  cout.precision(3);
  cout << fixed << total_value << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}