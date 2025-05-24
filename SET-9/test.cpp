#include <bits/stdc++.h>

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
  StringGenerator()
      : rng(time(nullptr)),
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

  vector<string> generate_random_strings(size_t count) {
    vector<string> result;
    for (size_t i = 0; i < count; ++i) {
      result.push_back(generate_string());
    }
    return result;
  }

  vector<string> generate_reversed_strings(size_t count) {
    auto arr = generate_random_strings(count);
    sort(arr.rbegin(), arr.rend());
    return arr;
  }

  vector<string> generate_almost_sorted_strings(size_t count, int swaps = 10) {
    auto arr = generate_random_strings(count);
    sort(arr.begin(), arr.end());
    uniform_int_distribution<size_t> idx_dist(0, count-1);
    for (int i = 0; i < swaps; ++i) {
      size_t a = idx_dist(rng);
      size_t b = idx_dist(rng);
      swap(arr[a], arr[b]);
    }
    return arr;
  }
};
