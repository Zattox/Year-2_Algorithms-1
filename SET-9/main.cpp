#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

class StringGenerator {
 private:
  const string available_chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789"
      "!@#%:;^&*()-.";

  mt19937 rng;
  uniform_int_distribution<size_t> char_dist;
  uniform_int_distribution<size_t> len_dist;

 public:
  StringGenerator() :
      rng(std::time(nullptr)),
      char_dist(0, available_chars.size() - 1),
      len_dist(10, 200) {}

  string generate_string() {
    size_t length = len_dist(rng);
    string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
      result += available_chars[char_dist(rng)];
    }

    return result;
  }

  vector<string> generate_strings(size_t count) {
    vector<string> result;
    result.reserve(count);

    for (size_t i = 0; i < count; ++i) {
      result.push_back(generate_string());
    }

    return result;
  }
};

int main() {
  StringGenerator generator;

  auto strings = generator.generate_strings(5);

  return 0;
}

/*
vector<string> solve(vector<string> &arr) {
  auto [sorted_arr, lcp_arr] = mergeSort(arr);
  return sorted_arr;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  StringGenerator generator;

  while (true) {
    mt19937 rnd;
    int n = rnd() % 20;
    auto strings = generator.generate_strings(n);

    auto corr = strings;
    std::sort(corr.begin(), corr.end());
    auto question = strings;
    auto ans = solve(question);

    if (corr != ans) {
      cout << "ERROR\n";
      for (auto el : strings) {
        cout << el << '\n';
      }
      cout << "\n=================\n";
      for (auto el : corr) {
        cout << el << '\n';
      }
      cout << "\n=================\n";
      for (auto el : ans) {
        cout << el << '\n';
      }
      cout << "\n=================\n";
      break;
    }
  }
}
*/