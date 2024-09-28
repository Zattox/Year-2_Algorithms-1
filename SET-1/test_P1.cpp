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
  List b;

  b.head = new Node(0);
  b.head->next = new Node(1);
  b.head->next->prev = b.head;
  b.head->next->next = b.head;
  b.tail = b.head->next;
  b._size = 2;

  cout << b.check_cycle();

}