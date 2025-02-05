#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

map<char, string> convertor = {{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
                               {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
                               {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
                               {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

vector<int> hex_to_line(string num, int n) {
  string fullbin;
  for (auto el : num) {
    fullbin += convertor[el];
  }
  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    ans.push_back(fullbin[i] - '0');
  }
  return ans;
}

void str_to_matrix(vector<vector<int>> &a, int n) {
  for (int i = 0; i < n; ++i) {
    string num;
    cin >> num;
    a.push_back(hex_to_line(num, n));
  }
}

vector<int> create_random_vector(int n) {
  random_device rand_dev;
  mt19937 generator(rand_dev());
  uniform_int_distribution<> distr(0, 1);
  vector<int> vec(n);
  for (int i = 0; i < n; ++i) {
    vec[i] = distr(generator);
  }
  return vec;
}

vector<int> special_mul(vector<vector<int>> &mat, vector<int> &r) {
  int n = r.size();
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ans[i] = (ans[i] + mat[i][j] * r[j]) % 2;
    }
  }
  return ans;
}

bool check_mul(vector<vector<int>> &a, vector<vector<int>> &b, vector<vector<int>> &c, int n) {
  vector<int> r = create_random_vector(n);
  auto Br = special_mul(b, r);
  auto X = special_mul(a, Br);
  auto Y = special_mul(c, r);
  return (X == Y);
}

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> a, b, c;

  str_to_matrix(a, n);
  str_to_matrix(b, n);
  str_to_matrix(c, n);

  for (int i = 0; i < 20; ++i) {
    if (!check_mul(a, b, c, n)) {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = 1;
  // cin >> t;
  while (t > 0) {
    solve();
    --t;
  }
}
