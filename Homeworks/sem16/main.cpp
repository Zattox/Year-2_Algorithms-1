#include <iostream>
#include <algorithm>
#include "SkipList.cpp"
#include "avl_tree.cpp"

using namespace std;

void runTest(const vector<int> &arr, const vector<int> &search_arr) {
  SkipList skipList;
  AVLTree avl_tree;

  for (auto el : arr) {
    skipList.insert(el);
    avl_tree.insert(el);
  }

  for (auto el : search_arr) {
    auto res1 = skipList.search(el);
    auto res2 = avl_tree.find(el);
  }

  int sz = (int) search_arr.size();
  double skip_result = static_cast<double>(skipList.totalFindOperations) / sz;
  double avl_result = static_cast<double>(avl_tree.totalFindOperations) / sz;

  std::cout << "Average operations for find in SkipList: " << skip_result << std::endl;
  std::cout << "Average operations for find in AVLTree: " << avl_result << std::endl;
}

void test1() {
  cout << "==============Small size + sorted numbers==============\n";
  vector<int> arr = {12, 17, 20, 25, 31, 38, 39, 44, 50, 55};
  vector<int> search_arr = {12, 17, 11, 2, 3, 5, 1, 44, 50, 55};
  runTest(arr, search_arr);
  cout << "=======================================================" << endl;
}

void test2() {
  mt19937 getRand(time(nullptr));

  cout << "===============Big size + sorted numbers===============\n";
  int len = 200000;
  vector<int> arr, search_arr;

  for (int _ = 0; _ < len; ++_) {
    int el1 = getRand() % 100000;
    arr.push_back(el1);
    if (getRand() % 2 == 0) {
      search_arr.push_back(el1);
    } else {
      search_arr.push_back(getRand() % 100000);
    }
  }
  std::sort(arr.begin(), arr.end());

  runTest(arr, search_arr);
  cout << "=======================================================" << endl;
}

void test3() {
  cout << "=============Small size + unsorted numbers=============\n";
  vector<int> arr = {123, 12, 2, 11, 4, 2, 567, 122, 5, 71};
  vector<int> search_arr = {12, 2, 567, 122, 5, 71, 1, 44, 50, 55};

  runTest(arr, search_arr);
  cout << "=======================================================" << endl;
}

void test4() {
  mt19937 getRand(time(nullptr));

  cout << "==============Big size + unsorted numbers==============\n";
  int len = 200000;
  vector<int> arr, search_arr;

  for (int _ = 0; _ < len; ++_) {
    int el1 = getRand() % 100000;
    arr.push_back(el1);
    if (getRand() % 2 == 0) {
      search_arr.push_back(el1);
    } else {
      search_arr.push_back(getRand() % 100000);
    }
  }

  runTest(arr, search_arr);
  cout << "=======================================================" << endl;
}

int main() {

  test1();
  test2();
  test3();
  test4();

  return 0;
}

