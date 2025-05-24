#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
      : rng(chrono::steady_clock::now().time_since_epoch().count()),
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
    result.reserve(count);
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
    uniform_int_distribution<size_t> idx_dist(0, count - 1);
    for (int i = 0; i < swaps && count > 1; ++i) {
      size_t a = idx_dist(rng);
      size_t b = idx_dist(rng);
      if (a != b) swap(arr[a], arr[b]);
    }
    return arr;
  }

  vector<string> generate_prefix_strings(size_t count, const string& common_prefix = "test") {
    vector<string> result;
    result.reserve(count);
    for (size_t i = 0; i < count; ++i) {
      string suffix = generate_string();
      result.push_back(common_prefix + suffix);
    }
    return result;
  }
};

// Utility function to count character comparisons in string comparison
ll compare_strings(const string& a, const string& b, ll& comparisons) {
  size_t min_len = min(a.length(), b.length());
  for (size_t i = 0; i < min_len; ++i) {
    ++comparisons;
    if (a[i] != b[i]) {
      return a[i] < b[i] ? -1 : 1;
    }
  }
  if (a.length() != b.length()) {
    return a.length() < b.length() ? -1 : 1;
  }
  return 0;
}

// Standard QuickSort with comparison counting
int partition(vector<string>& arr, int low, int high, ll& comparisons) {
  const string& pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (compare_strings(arr[j], pivot, comparisons) < 0) {
      ++i;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return i + 1;
}

void quickSort(vector<string>& arr, int low, int high, ll& comparisons) {
  if (low < high) {
    int pi = partition(arr, low, high, comparisons);
    quickSort(arr, low, pi - 1, comparisons);
    quickSort(arr, pi + 1, high, comparisons);
  }
}

// Standard MergeSort with comparison counting
void merge(vector<string>& arr, int l, int m, int r, ll& comparisons) {
  vector<string> temp(r - l + 1);
  int i = l, j = m + 1, k = 0;

  while (i <= m && j <= r) {
    if (compare_strings(arr[i], arr[j], comparisons) <= 0) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= m) temp[k++] = arr[i++];
  while (j <= r) temp[k++] = arr[j++];

  for (int p = 0; p < k; ++p) {
    arr[l + p] = move(temp[p]);
  }
}

void mergeSort(vector<string>& arr, int l, int r, ll& comparisons) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, comparisons);
    mergeSort(arr, m + 1, r, comparisons);
    merge(arr, l, m, r, comparisons);
  }
}

// LCP-aware comparison
struct LCPResult {
  int cmp_result;
  size_t lcp_length;
};

LCPResult lcp_compare(const string& a, const string& b, size_t known_lcp = 0, ll& comparisons = *(new ll(0))) {
  size_t i = known_lcp;
  while (i < a.length() && i < b.length()) {
    ++comparisons;
    if (a[i] != b[i]) {
      return {a[i] < b[i] ? -1 : 1, i};
    }
    ++i;
  }

  if (a.length() == b.length()) {
    return {0, i};
  }
  return {a.length() < b.length() ? -1 : 1, i};
}

// String MergeSort with LCP optimization
void string_merge_sort(vector<string>& arr, vector<size_t>& lcp, int l, int r, ll& comparisons) {
  if (l >= r) return;

  int m = l + (r - l) / 2;
  string_merge_sort(arr, lcp, l, m, comparisons);
  string_merge_sort(arr, lcp, m + 1, r, comparisons);

  vector<string> temp(r - l + 1);
  int i = l, j = m + 1, k = 0;

  while (i <= m && j <= r) {
    LCPResult cmp = lcp_compare(arr[i], arr[j], 0, comparisons);
    if (cmp.cmp_result <= 0) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= m) temp[k++] = arr[i++];
  while (j <= r) temp[k++] = arr[j++];

  for (int p = 0; p < k; ++p) {
    arr[l + p] = move(temp[p]);
  }
}

// Ternary String QuickSort
char get_char(const string& s, int pos) {
  return pos < s.length() ? s[pos] : 0;
}

void ternary_string_quicksort(vector<string>& arr, int left, int right, int char_index, ll& comparisons) {
  if (left >= right) return;

  static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> dist(left, right);
  swap(arr[left], arr[dist(rng)]);

  char pivot_char = get_char(arr[left], char_index);
  int less_than = left, greater_than = right, current = left + 1;

  while (current <= greater_than) {
    char current_char = get_char(arr[current], char_index);
    ++comparisons;

    if (current_char < pivot_char) {
      swap(arr[less_than++], arr[current++]);
    } else if (current_char > pivot_char) {
      swap(arr[current], arr[greater_than--]);
    } else {
      ++current;
    }
  }

  ternary_string_quicksort(arr, left, less_than - 1, char_index, comparisons);
  if (pivot_char != 0) {
    ternary_string_quicksort(arr, less_than, greater_than, char_index + 1, comparisons);
  }
  ternary_string_quicksort(arr, greater_than + 1, right, char_index, comparisons);
}

// MSD Radix Sort
void msd_radix_sort(vector<string>& arr, int left, int right, int char_index, ll& comparisons, bool use_quicksort_cutoff = false) {
  if (left >= right) return;

  if (use_quicksort_cutoff && (right - left + 1) <= 74) {
    ternary_string_quicksort(arr, left, right, char_index, comparisons);
    return;
  }

  const int R = 256;
  vector<int> count(R + 2, 0);
  vector<string> aux(right - left + 1);

  for (int i = left; i <= right; ++i) {
    char c = get_char(arr[i], char_index);
    count[c + 2]++;
    if (char_index < arr[i].length()) ++comparisons;
  }

  for (int r = 0; r < R + 1; ++r) {
    count[r + 1] += count[r];
  }

  for (int i = left; i <= right; ++i) {
    char c = get_char(arr[i], char_index);
    aux[count[c + 1]++] = arr[i];
  }

  for (int i = left; i <= right; ++i) {
    arr[i] = aux[i - left];
  }

  for (int r = 0; r < R; ++r) {
    int start = left + count[r];
    int end = left + count[r + 1] - 1;
    if (start < end) {
      msd_radix_sort(arr, start, end, char_index + 1, comparisons, use_quicksort_cutoff);
    }
  }
}

class StringSortTester {
 public:
  enum SortType {
    QUICKSORT,
    MERGESORT,
    TERNARY_QUICKSORT,
    LCP_MERGESORT,
    MSD_RADIXSORT,
    MSD_RADIXSORT_WITH_QUICKSORT
  };

  struct MeasurementResult {
    ll comparisons;
    double time_milliseconds;
  };

  struct StatisticalResult {
    ll avg_comparisons;
    double avg_time_ms;
    double median_time_ms;
  };

 private:
  // Execute specific sorting algorithm with time measurement
  MeasurementResult execute_sort_algorithm(SortType type, vector<string> arr) {
    ll comparisons = 0;

    auto start = chrono::high_resolution_clock::now();

    switch (type) {
      case QUICKSORT:
        quickSort(arr, 0, arr.size() - 1, comparisons);
        break;
      case MERGESORT:
        mergeSort(arr, 0, arr.size() - 1, comparisons);
        break;
      case TERNARY_QUICKSORT:
        ternary_string_quicksort(arr, 0, arr.size() - 1, 0, comparisons);
        break;
      case LCP_MERGESORT: {
        vector<size_t> lcp(arr.size());
        string_merge_sort(arr, lcp, 0, arr.size() - 1, comparisons);
        break;
      }
      case MSD_RADIXSORT:
        msd_radix_sort(arr, 0, arr.size() - 1, 0, comparisons, false);
        break;
      case MSD_RADIXSORT_WITH_QUICKSORT:
        msd_radix_sort(arr, 0, arr.size() - 1, 0, comparisons, true);
        break;
    }

    auto end = chrono::high_resolution_clock::now();
    double time_ms = chrono::duration<double, milli>(end - start).count();

    return {comparisons, time_ms};
  }

  // Calculate statistical metrics
  StatisticalResult calculate_statistics(const vector<MeasurementResult>& results) {
    if (results.empty()) {
      return {0, 0.0, 0.0};
    }

    StatisticalResult stats;

    // Average comparisons
    ll total_comparisons = 0;
    for (const auto& result : results) {
      total_comparisons += result.comparisons;
    }
    stats.avg_comparisons = total_comparisons / results.size();

    // Time statistics
    vector<double> times;
    double total_time = 0.0;
    for (const auto& result : results) {
      times.push_back(result.time_milliseconds);
      total_time += result.time_milliseconds;
    }

    stats.avg_time_ms = total_time / results.size();

    // Median
    sort(times.begin(), times.end());
    if (times.size() % 2 == 0) {
      stats.median_time_ms = (times[times.size()/2 - 1] + times[times.size()/2]) / 2.0;
    } else {
      stats.median_time_ms = times[times.size()/2];
    }

    return stats;
  }

 public:
  // Main testing method with precise measurements
  StatisticalResult test_algorithm(SortType type, const vector<string>& original_data, int runs = 15) {
    vector<MeasurementResult> measurements;
    measurements.reserve(runs);

    for (int run = 0; run < runs; ++run) {
      MeasurementResult result = execute_sort_algorithm(type, original_data);
      measurements.push_back(result);
    }

    return calculate_statistics(measurements);
  }

  // Write CSV header
  void write_csv_header(ofstream& file) {
    file << "Size,Algorithm,DataType,AvgComparisons,AvgTime_ms,MedianTime_ms\n";
  }

  // Write result to CSV file
  void write_csv_result(ofstream& file, int size, const string& algorithm_name,
                        const string& data_type, const StatisticalResult& result) {
    file << size << "," << algorithm_name << "," << data_type
         << "," << result.avg_comparisons
         << "," << fixed << setprecision(3) << result.avg_time_ms
         << "," << result.median_time_ms << "\n";
  }

  // Comprehensive testing of all algorithms with file output
  void run_comprehensive_analysis(const string& output_filename = "string_sort_results.csv") {
    StringGenerator generator;

    // Full range of sizes from 100 to 3000 with step 100
    vector<int> sizes;
    for (int size = 100; size <= 3000; size += 100) {
      sizes.push_back(size);
    }

    vector<SortType> algorithms = {
        QUICKSORT, MERGESORT, TERNARY_QUICKSORT,
        LCP_MERGESORT, MSD_RADIXSORT, MSD_RADIXSORT_WITH_QUICKSORT
    };

    vector<string> algorithm_names = {
        "QuickSort", "MergeSort", "Ternary_QuickSort",
        "LCP_MergeSort", "MSD_RadixSort", "MSD_RadixSort_QuickSort"
    };

    // Open file for writing
    ofstream csv_file(output_filename);
    if (!csv_file.is_open()) {
      cerr << "Error: Cannot create output file " << output_filename << endl;
      return;
    }

    cout << "Results will be saved to: " << output_filename << endl;
    cout << "Testing " << algorithms.size() << " algorithms on " << sizes.size() << " different sizes\n\n";

    // Write header
    write_csv_header(csv_file);

    // Test each algorithm on all sizes and data types
    for (size_t alg_idx = 0; alg_idx < algorithms.size(); ++alg_idx) {
      cout << "Testing " << algorithm_names[alg_idx] << "..." << endl;

      for (int size : sizes) {
        // Generate test data for current size
        vector<pair<string, vector<string>>> test_datasets = {
            {"Random", generator.generate_random_strings(size)},
            {"Reversed", generator.generate_reversed_strings(size)},
            {"Almost_Sorted", generator.generate_almost_sorted_strings(size, size/20)},
            {"Common_Prefix", generator.generate_prefix_strings(size, "common_prefix_")}
        };

        for (auto& [data_type, dataset] : test_datasets) {
          StatisticalResult result = test_algorithm(algorithms[alg_idx], dataset);
          write_csv_result(csv_file, size, algorithm_names[alg_idx], data_type, result);
        }
      }
      cout << "  Completed testing " << algorithm_names[alg_idx] << endl;
    }

    csv_file.close();
    cout << "\nAnalysis completed. Results saved to: " << output_filename << endl;
  }
};

int main() {
  StringSortTester tester;

  cout << "String Sorting Performance Analysis\n";
  cout << "==================================\n\n";

  // Run comprehensive analysis with file output
  tester.run_comprehensive_analysis();

  cout << "\nAnalysis completed successfully!\n";
  cout << "Check the CSV file for detailed results.\n";

  return 0;
}