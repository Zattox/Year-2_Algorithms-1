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
  List x;
  x.push_back(2);
  print_list(x);

  List y(x);
  y.replace(2, 4);
  print_list(y);


  vector<int> asttt({12, 1, 1, 21});
  List z(asttt);
  print_list(z);
}