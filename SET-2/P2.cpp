#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll kBase = 1000000000;

void RemoveLeadingZeros(vector<ll> &result) {
  while (result.size() > 1 && result.back() == 0) {
    result.pop_back();
  }
}

vector<ll> input_func(string &value) {
  vector<ll> digits;
  for (auto i = static_cast<int64_t>(value.size()); i > 0; i -= 9) {
    if (i < 9) {
      digits.emplace_back(std::atoll(value.substr(0, i).c_str()));
    } else {
      digits.emplace_back(std::atoll(value.substr(i - 9, 9).c_str()));
    }
  }
  RemoveLeadingZeros(digits);
  return digits;
}

void solve() {
  string str1, str2;
  cin >> str1 >> str2;
  vector<ll> num1 = input_func(str1);
  vector<ll> num2 = input_func(str2);

  vector<ll> result(str1.size() + str2.size());
  for (size_t i = 0; i < num1.size(); ++i) {
    ll delta = 0;
    for (size_t j = 0; j < num2.size() || delta != 0; ++j) {
      ll cur_digit = delta + result[i + j];
      if (j < num2.size()) {
        cur_digit += 1LL * num1[i] * num2[j];
      }
      delta = cur_digit / kBase;
      result[i + j] = cur_digit % kBase;
    }
  }

  RemoveLeadingZeros(result);
  cout << result.back();
  auto old_fill = cout.fill('0');
  for (ll i = static_cast<int64_t>(result.size()) - 2; i >= 0; --i) {
    cout << std::setw(9) << result[i];
  }
  cout.fill(old_fill);
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
