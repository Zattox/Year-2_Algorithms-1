#include <bits/stdc++.h>

using namespace std;

void solve() {
  string input;
  getline(cin, input);

  unordered_map<string, int> stringToCode;
  for (int i = 0; i < 128; i++) {
    string s(1, static_cast<char>(i));
    stringToCode[s] = i;
  }

  int nextCode = 128;
  vector<int> codes;
  string w = "";

  for (char c : input) {
    string wc = w + c;
    if (stringToCode.find(wc) != stringToCode.end()) {
      w = wc;
    } else {
      if (!w.empty()) {
        codes.push_back(stringToCode[w]);
      }
      stringToCode[wc] = nextCode;
      nextCode++;
      w = string(1, c);
    }
  }

  if (!w.empty()) {
    codes.push_back(stringToCode[w]);
  }

  cout << codes.size() << "\n";
  for (size_t i = 0; i < codes.size(); i++) {
    cout << codes[i];
    if (i < codes.size() - 1) {
      cout << " ";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}