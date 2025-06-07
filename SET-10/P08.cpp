#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 179;

vector<vector<ll>> multiply(const vector<vector<ll>> &A, const vector<vector<ll>> &B) {
  int n = A.size();
  vector<vector<ll>> C(n, vector<ll>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
      }
    }
  }

  return C;
}

vector<vector<ll>> matrix_power(vector<vector<ll>> base, ll exp) {
  int n = base.size();
  vector<vector<ll>> result(n, vector<ll>(n, 0));

  for (int i = 0; i < n; i++) {
    result[i][i] = 1;
  }

  while (exp > 0) {
    if (exp & 1) {
      result = multiply(result, base);
    }
    base = multiply(base, base);
    exp >>= 1;
  }

  return result;
}

void solve() {
  ll n, k;
  cin >> n >> k;

  if (n == 1) {
    cout << k << "\n";
    return;
  }

  int states = 2 * k;
  vector<vector<ll>> transition(states, vector<ll>(states, 0));

  for (int v = 1; v <= k; v++) {
    for (int u = 1; u < v; u++) {
      transition[v - 1][k + u - 1] = 1;
    }

    for (int u = v + 1; u <= k; u++) {
      transition[k + v - 1][u - 1] = 1;
    }
  }

  vector<ll> initial(states, 1);

  if (n > 1) {
    vector<vector<ll>> result_matrix = matrix_power(transition, n - 1);

    vector<ll> final_state(states, 0);
    for (int i = 0; i < states; i++) {
      for (int j = 0; j < states; j++) {
        final_state[i] = (final_state[i] + result_matrix[i][j] * initial[j]) % MOD;
      }
    }
    initial = final_state;
  }

  ll ans = 0;
  for (int i = 0; i < states; i++) {
    ans = (ans + initial[i]) % MOD;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
}
