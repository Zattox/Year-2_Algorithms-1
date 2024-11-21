#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

const int max_num = 1000000;

vector<int> countingSort(vector<int> &arr, int n) {
  vector<int> ans, cnt(2 * (max_num + 1));
  for (int i = 0; i < n; ++i) {
    ++cnt[arr[i] + max_num];
  }
  for (int num = 0; num <= cnt.size(); ++num) {
    for (int i = 0; i < cnt[num]; ++i) {
      ans.push_back(num - max_num);
    }
  }
  return ans;
}

void solve() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  auto ans = countingSort(arr, n);
  for (auto el : ans) {
    cout << el << ' ';
  }


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
