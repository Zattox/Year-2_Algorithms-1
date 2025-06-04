#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

struct Item {
  int value;
  double weight;
  int index;
  double ratio;
};

struct Node {
  int level;
  int value;
  double weight;
  double bound;
  vector<bool> taken;
};

double calculate_bound(const Node &node, int n, const vector<Item> &items, double capacity) {
  if (node.weight >= capacity) return 0;

  double bound = node.value;
  double weight = node.weight;
  int level = node.level;

  while (level < n && weight + items[level].weight <= capacity) {
    weight += items[level].weight;
    bound += items[level].value;
    level++;
  }

  if (level < n) {
    bound += (capacity - weight) * items[level].ratio;
  }

  return bound;
}

void branch_boundary_method(int n, const vector<int> &c, const vector<double> &w, double capacity = 100.0) {
  vector<Item> items(n);
  for (int i = 0; i < n; i++) {
    items[i] = {c[i], w[i], i, (double) c[i] / w[i]};
  }

  sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
    return a.ratio > b.ratio;
  });

  priority_queue<Node, vector<Node>, function<bool(const Node &, const Node &)>> pq(
      [](const Node &a, const Node &b) { return a.bound < b.bound; }
  );

  Node root = {0, 0, 0.0, 0.0, vector<bool>(n, false)};
  root.bound = calculate_bound(root, n, items, capacity);
  pq.push(root);

  int max_value = 0;
  vector<bool> best_solution(n, false);

  while (!pq.empty()) {
    Node current = pq.top();
    pq.pop();

    if (current.bound <= max_value) continue;

    if (current.level == n) {
      if (current.value > max_value) {
        max_value = current.value;
        best_solution = current.taken;
      }
      continue;
    }

    if (current.weight + items[current.level].weight <= capacity) {
      Node with_item = current;
      with_item.level++;
      with_item.value += items[current.level].value;
      with_item.weight += items[current.level].weight;
      with_item.taken[items[current.level].index] = true;
      with_item.bound = calculate_bound(with_item, n, items, capacity);

      if (with_item.bound > max_value) {
        pq.push(with_item);
      }
    }

    Node without_item = current;
    without_item.level++;
    without_item.bound = calculate_bound(without_item, n, items, capacity);

    if (without_item.bound > max_value) {
      pq.push(without_item);
    }
  }
}

void standard_method(int n, const vector<int> &c, const vector<double> &w, double capacity = 100.0) {
  vector<int> int_weights(n);
  int int_capacity = (int) (capacity * 100);

  for (int i = 0; i < n; i++) {
    int_weights[i] = (int) (w[i] * 100);
  }

  vector<vector<int>> dp(n + 1, vector<int>(int_capacity + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int weight = 0; weight <= int_capacity; weight++) {
      dp[i][weight] = dp[i - 1][weight];

      if (weight >= int_weights[i - 1]) {
        dp[i][weight] = max(dp[i][weight], dp[i - 1][weight - int_weights[i - 1]] + c[i - 1]);
      }
    }
  }
}

void gen_test(int &n, vector<int> &c, vector<double> &w) {
  random_device rd;
  mt19937_64 engine(rd());
  uniform_real_distribution<double> weight_dist(0.1, 10.0);
  uniform_int_distribution<int> value_dist(1, 200);

  c.resize(n);
  w.resize(n);
  for (int i = 0; i < n; ++i) {
    c[i] = value_dist(engine);
    w[i] = weight_dist(engine);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << "=== Performance Research ===" << endl;
  cout << "n\tBranch & Bound\tStandard Method\tRatio" << endl;

  vector<int> arr_n;
  for (int i = 10; i <= 100; i += 10) {
    arr_n.push_back(i);
  }
  for (int i = 200; i <= 2000; i += 100) {
    arr_n.push_back(i);
  }
  for (int i = 3000; i <= 10000; i += 1000) {
    arr_n.push_back(i);
  }

  for (auto n : arr_n) {
    vector<int> c;
    vector<double> w;
    gen_test(n, c, w);

    auto start = high_resolution_clock::now();
    branch_boundary_method(n, c, w);
    auto end = high_resolution_clock::now();
    auto time_branch = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    standard_method(n, c, w);
    end = high_resolution_clock::now();
    auto time_standard = duration_cast<microseconds>(end - start);

    double ratio = (double) time_branch.count() / (double) time_standard.count();

    cout << n << "\t" << time_branch.count() << "\t\t\t"
         << time_standard.count() << "\t\t\t"
         << fixed << setprecision(2) << ratio << endl;
  }

  return 0;
}
