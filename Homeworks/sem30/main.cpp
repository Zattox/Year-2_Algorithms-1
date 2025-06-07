#include <bits/stdc++.h>

typedef long double ld;

using namespace std;
using namespace chrono;

struct Item {
  int value;
  ld weight;
  int index;
  ld ratio;
};

struct Node {
  int level;
  int value;
  ld weight;
  ld bound;
  vector<bool> taken;
};

struct Result {
  int max_value;
  long long time_microseconds;
};

ld calculate_bound(const Node &node, int n, const vector<Item> &items, ld capacity) {
  if (node.weight >= capacity) return 0;

  ld bound = node.value;
  ld weight = node.weight;
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

Result branch_boundary_method(int n, const vector<int> &c, const vector<ld> &w, ld capacity) {
  auto start = high_resolution_clock::now();

  vector<Item> items(n);
  for (int i = 0; i < n; i++) {
    items[i] = {c[i], w[i], i, (ld) c[i] / w[i]};
  }

  sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
    return a.ratio > b.ratio;
  });

  priority_queue<Node, vector<Node>, function<bool(
      const Node &, const Node &)>> pq(
      [](const Node &a, const Node &b) { return a.bound < b.bound; }
  );

  Node root = {0, 0, 0.0, 0.0, vector<bool>(n, false)};
  root.bound = calculate_bound(root, n, items, capacity);
  pq.push(root);

  int max_value = 0;

  while (!pq.empty()) {
    Node current = pq.top();
    pq.pop();

    if (current.bound <= max_value) {
      continue;
    }

    if (current.level == n) {
      if (current.value > max_value) {
        max_value = current.value;
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

  auto end = high_resolution_clock::now();
  auto time_taken = duration_cast<microseconds>(end - start);

  return {max_value, time_taken.count()};
}

Result standard_method(int n, const vector<int> &c, const vector<ld> &w, ld capacity) {
  auto start = high_resolution_clock::now();

  vector<int> int_weights(n);
  int int_capacity = (int) (capacity * 100);

  for (int i = 0; i < n; i++) {
    int_weights[i] = (int) (w[i] * 100);
  }

  vector<vector<int>> dp(n + 1, vector<int>(int_capacity + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int weight = 1; weight <= int_capacity; weight++) {
      dp[i][weight] = dp[i - 1][weight];

      if (weight >= int_weights[i - 1]) {
        dp[i][weight] = max(dp[i][weight], dp[i - 1][weight - int_weights[i - 1]] + c[i - 1]);
      }
    }
  }

  auto end = high_resolution_clock::now();
  auto time_taken = duration_cast<microseconds>(end - start);

  return {dp[n][int_capacity], time_taken.count()};
}

void gen_test(int n, vector<int> &c, vector<ld> &w, ld &capacity) {
  random_device rd;
  mt19937_64 engine(rd());
  uniform_int_distribution<int> weight_int_dist(100, 1000);
  uniform_int_distribution<int> value_dist(1, 200);
  uniform_int_distribution<int> capacity_int_dist(1000, 20000);

  c.resize(n);
  w.resize(n);

  for (int i = 0; i < n; ++i) {
    c[i] = value_dist(engine);
    w[i] = weight_int_dist(engine) / 100.0;
  }

  capacity = capacity_int_dist(engine) / 100.0;
}

int main() {
  cout << "=== Knapsack Problem Performance Research ===" << endl;
  cout << "n\tCapacity\tBranch&Bound(μs)\tStandard(μs)\tRatio" << endl;
  cout << string(70, '-') << endl;

  vector<int> arr_n;
  for (int i = 10; i <= 100; i += 10) {
    arr_n.push_back(i);
  }
  for (int i = 200; i <= 1000; i += 100) {
    arr_n.push_back(i);
  }
  for (int i = 2000; i <= 10000; i += 1000) {
    arr_n.push_back(i);
  }

  int total_tests = 0;

  for (auto n : arr_n) {
    vector<int> c;
    vector<ld> w;
    ld capacity;

    gen_test(n, c, w, capacity);
    total_tests++;

    Result result_branch = branch_boundary_method(n, c, w, capacity);
    Result result_standard = standard_method(n, c, w, capacity);

    bool values_match = (result_branch.max_value == result_standard.max_value);

    if (!values_match) {
      cout << "\nERROR: Results mismatch for n=" << n << endl;
      cout << "Branch & Bound: " << result_branch.max_value << endl;
      cout << "Standard DP: " << result_standard.max_value << endl;
      cout << "Capacity: " << fixed << setprecision(2) << capacity << endl;
      cout << "Testing stopped!" << endl;
      return 1;
    }

    ld ratio = (result_branch.time_microseconds > 0) ?
               (ld) result_standard.time_microseconds / (ld) result_branch.time_microseconds : 0.0;

    cout << n << "\t" << fixed << setprecision(1) << capacity << "\t\t"
         << result_branch.time_microseconds << "\t\t\t"
         << result_standard.time_microseconds << "\t\t"
         << setprecision(2) << ratio << endl;
  }

  cout << string(70, '-') << endl;
  cout << "All " << total_tests << " tests passed!" << endl;

  return 0;
}