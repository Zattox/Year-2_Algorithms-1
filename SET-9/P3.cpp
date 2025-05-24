#include <bits/stdc++.h>

using namespace std;

void solve() {
  int k;
  cin >> k;

  vector<int> codes(k);
  for (int i = 0; i < k; i++) {
    cin >> codes[i];
  }

  vector<string> dictionary(128);
  for (int i = 0; i < 128; i++) {
    dictionary[i] = string(1, static_cast<char>(i));
  }

  int nextCode = 128;
  if (k == 0) {
    cout << "\n";
    return;
  }

  int code = codes[0];
  string current = dictionary[code];
  cout << current;
  string previous = current;

  for (size_t i = 1; i < k; i++) {
    code = codes[i];
    string entry;
    if (code < nextCode) {
      entry = dictionary[code];
    } else if (code == nextCode) {
      entry = previous + previous[0];
    } else {
      entry = "";
    }

    cout << entry;

    if (!entry.empty()) {
      string newString = previous + entry[0];
      dictionary.push_back(newString);
      nextCode++;
    }

    previous = entry;
  }

  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}