#include <bits/stdc++.h>

using namespace std;

vector<int> run_pref_func(string &s) {
  int n = s.length();
  vector<int> p(n, 0);

  for (int i = 1; i < n; ++i) {
    int cur = p[i - 1];
    while (cur > 0 && s[i] != s[cur]) {
      cur = p[cur - 1];
    }
    if (s[i] == s[cur])
      ++cur;
    p[i] = cur;
  }

  return p;
}

string construct_string(vector<int> &pref) {
  int n = pref.size();
  string s(n, ' ');

  if (pref[0] != 0) {
    return "";
  }
  for (int i = 1; i < n; ++i) {
    if (pref[i] > i + 1 || (pref[i] > 0 && pref[i - 1] < pref[i] - 1)) {
      return "";
    }
  }

  char next_char = 'a';
  for (int i = 0; i < n; ++i) {
    if (pref[i] == 0) {
      s[i] = next_char++;
    } else {
      s[i] = s[pref[i] - 1];
    }
  }

  return s;
}

void run_test(vector<int> pref) {
  cout << "Input Prefix function: ";
  for (int el : pref) {
    cout << el << ' ';
  }
  cout << endl;

  string s = construct_string(pref);
  if (s.empty()) {
    cout << "Incorrect Prefix function (#_#)" << endl;
  } else {
    cout << "Constructed string: " << s << endl;

    vector<int> result_pref = run_pref_func(s);
    cout << "Output Prefix function: ";
    for (int el : result_pref) {
      cout << el << ' ';
    }
    cout << endl;

    bool flag = true;
    for (int i = 0; i < pref.size(); ++i) {
      if (pref[i] != result_pref[i]) {
        flag = false;
        break;
      }
    }

    if (flag) {
      cout << "Success!" << endl;
    } else {
      cout << "Error :(" << endl;
    }
  }
  cout << endl;
}

int main() {
  vector<string> test = {"aaabaab", "abracadabra", "aaaaa", "abacaba", "Hello"};

  for (auto el : test) {
    run_test(run_pref_func(el));
  }

  run_test({1, 0, 0});
  run_test({0, 1, 0});
  run_test({0, 0, 0});

  return 0;
}
