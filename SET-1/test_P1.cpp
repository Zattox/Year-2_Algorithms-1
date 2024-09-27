#include "list.h"
#include "P1.cpp"
#include <iostream>

using namespace std;

void print_list(List l) {
  auto cur = l.head;
  while (cur != nullptr) {
    cout << cur->value << " ";
    cur = cur->next;
  }
  cout << "\n";
  return;
}

int main() {
  List a({122, 101, 2212, 122, 122});
  print_list(a);

  a.remove_duplicates();
  print_list(a);
  a.reverse();
  print_list(a);
}