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
  List a({1, 2, 3, 4, 5});
  List b({11, 22, 33, 44, 55});
  print_list(a);

  a.merge(b);
  print_list(a);
}