#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

std::random_device rnd_device;
std::mt19937 rnd(rnd_device());
std::uniform_int_distribution<> dis(0, 1e6);

ll quadratic_probe(ll val, ll i, ll M, vector<ld> &c) {
  ll c1 = ll(1ll * c[0] * i);
  ll c2 = ll(1ll * c[1] * i * i);
  ll ans = (val + c1 + c2) % M;
  return ans;
}

ll cubic_probe(ll val, ll i, ll M, vector<ld> &c) {
  ll c1 = ll(1ll * c[0] * i);
  ll c2 = ll(1ll * c[1] * i * i);
  ll c3 = ll(1ll * c[2] * i * i * i);
  ll ans = (0ll + val + c1 + c2 + c3) % M;
  return ans;
}

pair<ll , ld> simulate(ll numberOfKeys, ll M, vector<ld> c, ll (*probe)(ll, ll, ll, vector<ld> &)) {
  vector<ll> table(M, -1);
  ll collisions = 0, total_steps = 0;

  for (int _ = 0; _ < numberOfKeys; ++_) {
    ll new_key = dis(rnd);
    ll hash_val = new_key % M;
    ll i = 0;

    while (i < numberOfKeys) {
      ll index = probe(hash_val, i, M, c);
      if (table[index] == -1) {
        table[index] = new_key;
        break;
      } else {
        ++collisions;
        ++i;
      }
    }

    total_steps += i;
  }

  ld avg_steps = ld(total_steps) / numberOfKeys;
  return {collisions, avg_steps};
}

pair<ll, ld> findBest(vector<pair<ll, ld>> arr) {
  pair<int, double> ans = {1e9, 1e9};
  for (auto el : arr) {
    if (el.second < ans.second) {
      ans = el;
    }
  }
  return ans;
}

void solve(string text, vector<ll> &valueOfM) {
  cout << "Test, where M is " << text;

  for (ll M : valueOfM) {
    cout << endl << "M = " << M << ":" << endl;
    ll numberOfKeys = M;
    auto quad_result1 = simulate(numberOfKeys, M, {1, 1}, quadratic_probe);
    auto quad_result2 = simulate(numberOfKeys, M, {0.5, 0.5}, quadratic_probe);
    auto quad_result3 = simulate(numberOfKeys, M, {1, 0.5}, quadratic_probe);
    auto quad_result4 = simulate(numberOfKeys, M, {0, 1}, quadratic_probe);
    auto best_quad = findBest({quad_result1, quad_result2, quad_result3, quad_result4});
    cout << "Quadratic:\nCollisions = " << best_quad.first << endl;
    cout << "Average steps = " << std::setprecision(3) << best_quad.second << endl;

    auto cubic_result1 = simulate(numberOfKeys, M, {1, 1, 1}, cubic_probe);
    auto cubic_result2 = simulate(numberOfKeys, M, {0.5, 0.5, 0.5}, cubic_probe);
    auto cubic_result3 = simulate(numberOfKeys, M, {1, 0.5, 0.25}, cubic_probe);
    auto cubic_result4 = simulate(numberOfKeys, M, {0, 1, 0}, cubic_probe);
    auto cubic_result5 = simulate(numberOfKeys, M, {0.5, 0.25, 0.125}, cubic_probe);
    auto best_cubic = findBest({cubic_result1, cubic_result2, cubic_result3, cubic_result4, cubic_result5});

    cout << "Cubic:\nCollisions = " << best_cubic.first << endl;
    cout << "Average steps = " << std::setprecision(3) << best_cubic.second << endl;
  }
  cout << "=========END TEST GROUP=========\n" << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  vector<ll> powOf2 = {128, 256, 512, 1024, 2048, 4196};
  vector<ll> powOf3 = {9, 27, 243, 2187, 651};
  vector<ll> powOf10 = {10, 100, 1000, 10000, 100000};
  vector<ll> primeNumbers = {11, 101, 547, 1051, 5059, 10007, 51971, 99347};
  vector<ll> randomNumbers;
  for (int i = 0; i < 7; ++i) {
    randomNumbers.push_back(dis(rnd) + 2);
  }
  std::sort(randomNumbers.begin(), randomNumbers.end());

  solve("pow of 2", powOf2);
  solve("pow of 3", powOf3);
  solve("pow of 10", powOf10);
  solve("prime number", primeNumbers);
  solve("random number", randomNumbers);
}