#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> best_grid = {
    {2, 1, 1, 3, 2, 2, 3, 2, 1, 3},
    {1, 3, 1, 2, 2, 3, 2, 1, 2, 3},
    {3, 2, 2, 2, 1, 3, 3, 2, 1, 1},
    {2, 3, 1, 2, 1, 1, 3, 3, 3, 2},
    {1, 1, 3, 1, 1, 3, 2, 2, 3, 2},
    {3, 3, 2, 3, 1, 2, 1, 1, 2, 2},
    {2, 2, 1, 1, 3, 3, 1, 3, 2, 1},
    {3, 2, 3, 1, 3, 2, 2, 1, 1, 3},
    {1, 2, 3, 3, 2, 1, 1, 3, 1, 2},
    {2, 1, 2, 3, 3, 1, 2, 1, 3, 1}
};

vector<vector<int>> grid(10, vector<int>(10));
mt19937 rng(time(nullptr));

int calculateCost(int n, int m) {
  int cost = 0;
  for (int x1 = 0; x1 < n; x1++) {
    for (int x2 = x1 + 1; x2 < n; x2++) {
      for (int y1 = 0; y1 < m; y1++) {
        for (int y2 = y1 + 1; y2 < m; y2++) {
          if (grid[x1][y1] == grid[x1][y2] &&
              grid[x1][y1] == grid[x2][y1] &&
              grid[x1][y1] == grid[x2][y2]) {
            cost++;
          }
        }
      }
    }
  }
  return cost;
}

bool isValidSolution(int n, int m) {
  return calculateCost(n, m) == 0;
}

int calculateDeltaCost(int n, int m, int i, int j, int newColor) {
  int oldColor = grid[i][j];
  if (oldColor == newColor)
    return 0;

  int delta = 0;

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      if (x == i || y == j)
        continue;

      int corners[4] = {
          (x == i && y == j) ? newColor : grid[x][y],
          (x == i) ? newColor : grid[x][j],
          (y == j) ? newColor : grid[i][y],
          newColor
      };

      int oldCorners[4] = {
          grid[x][y], grid[x][j], grid[i][y], oldColor
      };

      bool oldBad = (oldCorners[0] == oldCorners[1] &&
          oldCorners[1] == oldCorners[2] &&
          oldCorners[2] == oldCorners[3]);

      bool newBad = (corners[0] == corners[1] &&
          corners[1] == corners[2] &&
          corners[2] == corners[3]);

      if (newBad && !oldBad)
        delta++;
      if (!newBad && oldBad)
        delta--;
    }
  }

  return delta;
}

bool simulatedAnnealing(int n, int m, int c) {
  double temperature = 100.0;
  double coolingRate = 0.95;
  double minTemperature = 0.01;

  int currentCost = calculateCost(n, m);

  while (temperature > minTemperature) {
    for (int iter = 0; iter < n * m * 10; iter++) {
      int i = rng() % n;
      int j = rng() % m;
      int newColor = rng() % c + 1;

      if (newColor == grid[i][j]) {
        continue;
      }

      int delta = calculateDeltaCost(n, m, i, j, newColor);
      auto x = uniform_real_distribution<double>(0, 1)(rng);
      if (delta < 0 || (delta > 0 && x < exp(-delta / temperature))) {
        grid[i][j] = newColor;
        currentCost += delta;

        if (currentCost == 0) return true;
      }
    }
    temperature *= coolingRate;
  }

  return currentCost == 0;
}

void generateRandomColoring(int n, int m, int c) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      grid[i][j] = rng() % c + 1;
    }
  }
}

void solve(int n, int m, int c) {
  generateRandomColoring(n, m, c);
  for (int attempt = 0; attempt < 100; ++attempt) {
    simulatedAnnealing(n, m, c);
    if (isValidSolution(n, m)) {
      return;
    }
  }
}

void printSolution(int n, int m, vector<vector<int>> &g) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << g[i][j] << " ";
    }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, c;
  cin >> n >> m >> c;

  if (c == 2) {
    solve(n, m, c);
    printSolution(n, m, grid);
  } else {
    printSolution(n, m, best_grid);
  }
}