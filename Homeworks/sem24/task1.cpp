#include <bits/stdc++.h>

using namespace std;

vector<int> run_z_func(string &s) {
  int n = s.length(), l = 0, r = 0;
  vector<int> z(n, 0);

  for (int i = 1; i < n; ++i) {
    if (r >= i)
      z[i] = min(z[i - l], r - i + 1);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }

  return z;
}

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

vector<int> z_to_pref(vector<int> &z) {
  int n = z.size();
  vector<int> pref(n, 0);

  for (int i = 1; i < n; i++) {
    if (z[i] > 0) {
      for (int j = z[i] - 1; j >= 0 && pref[i + j] == 0; --j) {
        pref[i + j] = j + 1;
      }
    }
  }

  return pref;
}

vector<int> pref_to_z(const vector<int> &pref) {
  int n = pref.size();
  vector<int> z(n, 0);

  // Шаг 1: Устанавливаем начальные значения z на основе pref
  for (int i = 1; i < n; ++i) {
    if (pref[i] > 0) {
      z[i - pref[i] + 1] = pref[i];
    }
  }

  // Шаг 2: Заполняем промежуточные значения z
  int i = 1;
  while (i < n) {
    if (z[i] == 0) {
      ++i;
      continue;
    }
    int j = 1;
    while (j < z[i] && i + j < n) {
      int v = min(z[j], z[i] - j);
      if (v >= z[i + j]) {
        z[i + j] = v;
        ++j;
      } else {
        break;
      }
    }
    i += j;
  }

  return z;
}

void run_test(string &s) {
  cout << "Test: " << s << endl;
  vector<int> z = run_z_func(s);
  vector<int> pref = run_pref_func(s);
  vector<int> result_z_to_pref = z_to_pref(z);
  vector<int> result_pref_to_z = pref_to_z(pref);

  cout << "Z-function: ";
  for (int i = 0; i < s.length(); ++i)
    cout << z[i] << ' ';

  cout << endl << "Prefix-function: ";
  for (int i = 0; i < s.length(); ++i)
    cout << pref[i] << ' ';

  bool flag1 = true;
  cout << endl << "Result of Z to Prefix: ";
  for (int i = 0; i < s.length(); ++i) {
    cout << result_z_to_pref[i] << ' ';
    if (result_z_to_pref[i] != pref[i])
      flag1 = false;
  }

  bool flag2 = true;
  cout << endl << "Result of Prefix to Z: ";
  for (int i = 0; i < s.length(); ++i) {
    cout << result_pref_to_z[i] << ' ';
    if (result_pref_to_z[i] != z[i])
      flag2 = false;
  }

  cout << endl;
  if (flag1) {
    cout << "Correct transformation Z to Prefix!" << endl;
  } else {
    cout << "Incorrect transformation Z to Prefix :(" << endl;
  }
  if (flag2) {
    cout << "Correct transformation Prefix to Z!" << endl;
  } else {
    cout << "Incorrect transformation Prefix to Z :(" << endl;
  }

  cout << "\n" << endl;
}

int main() {
  vector<string> test = {"aaabaab", "abracadabra", "aaaaa", "abacaba", "Hello"};

  for (auto el : test) {
    run_test(el);
  }

  return 0;
}
