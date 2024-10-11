#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<ll>> a, b;

void find_part_result(vector<vector<ll>> &matrix, vector<vector<ll>> &&part_a, vector<vector<ll>> &&part_b, int start_i, int start_j) {
  int delta = matrix.size() / 2;
  for (int i = start_i; i < start_i + delta; ++i) {
    for (int j = start_j; j < start_j + delta; ++j) {
      matrix[i][j] = part_a[i - start_i][j - start_j] + part_b[i - start_i][j - start_j];
    }
  }
}

vector<vector<ll>> mul_matrix(int si_a, int sj_a, int si_b, int sj_b, int n) {
  vector<vector<ll>> res(n, vector<ll>(n));

  if (n <= 256) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          res[i][j] += a[si_a + i][sj_a + k] * b[si_b + k][sj_b + j];
        }
      }
    }
  } else {
    int m = n / 2;

    find_part_result(res,
                     mul_matrix(si_a + 0, sj_a + 0, si_b + 0, sj_b + 0, m),
                     mul_matrix(si_a + 0, sj_a + m, si_b + m, sj_b + 0, m),
                     0, 0);

    find_part_result(res,
                     mul_matrix(si_a + 0, sj_a + 0, si_b + 0, sj_b + m, m),
                     mul_matrix(si_a + 0, sj_a + m, si_b + m, sj_b + m, m),
                     0, m);

    find_part_result(res,
                     mul_matrix(si_a + m, sj_a + 0, si_b + 0, sj_b + 0, m),
                     mul_matrix(si_a + m, sj_a + m, si_b + m, sj_b + 0, m),
                     m, 0);

    find_part_result(res,
                     mul_matrix(si_a + m, sj_a + 0, si_b + 0, sj_b + m, m),
                     mul_matrix(si_a + m, sj_a + m, si_b + m, sj_b + m, m),
                     m, m);
  }

  return res;
}

void solve() {
  int n;
  cin >> n;
  a.resize(n, vector<ll>(n));
  b.resize(n, vector<ll>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> b[i][j];
    }
  }

  vector<vector<ll>> c = mul_matrix(0, 0, 0, 0, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << c[i][j] << ' ';
    }
    cout << '\n';
  }
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
