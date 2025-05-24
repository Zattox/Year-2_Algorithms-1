#include <bits/stdc++.h>

using namespace std;

char getSymbol(const string &s, int ind) {
  return ind < s.size() ? s[ind] : 0;
}

void ternaryStringQuickSort(vector<string> &arr, int left, int right, int d) {
  if (left >= right)
    return;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(left, right);

  int pivotIndex = dis(gen);
  swap(arr[left], arr[pivotIndex]);
  char pivotChar = getSymbol(arr[left], d);

  int lt = left, gt = right, i = left + 1;
  while (i <= gt) {
    char currentChar = getSymbol(arr[i], d);
    if (currentChar < pivotChar) {
      swap(arr[lt], arr[i]);
      ++lt;
      ++i;
    } else if (currentChar > pivotChar) {
      swap(arr[i], arr[gt]);
      --gt;
    } else {
      ++i;
    }
  }

  ternaryStringQuickSort(arr, left, lt - 1, d);
  if (pivotChar != 0) {
    ternaryStringQuickSort(arr, lt, gt, d + 1);
  }
  ternaryStringQuickSort(arr, gt + 1, right, d);
}

void msdRadixSort(vector<string> &arr, int pos = 0) {
  if (arr.size() <= 1) return;

  if (arr.size() <= 74) {
    ternaryStringQuickSort(arr, 0, arr.size() - 1, pos);
    return;
  }

  vector<vector<string>> buckets(257);
  for (const auto &s : arr) {
    if (pos >= s.length()) {
      buckets[0].push_back(s);
    } else {
      unsigned char c = s[pos];
      buckets[c + 1].push_back(s);
    }
  }

  arr.clear();
  for (int i = 0; i < 257; ++i) {
    if (!buckets[i].empty()) {
      if (i == 0) {
        arr.insert(arr.end(), buckets[i].begin(), buckets[i].end());
      } else {
        msdRadixSort(buckets[i], pos + 1);
        arr.insert(arr.end(), buckets[i].begin(), buckets[i].end());
      }
    }
  }
}

void solve() {
  string n_str;
  getline(cin, n_str);
  int n = atoi(n_str.c_str());

  vector<string> arr(n);
  for (int i = 0; i < n; ++i) {
    getline(cin, arr[i]);
  }

  msdRadixSort(arr);

  for (const auto &el : arr) {
    cout << el << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
  return 0;
}