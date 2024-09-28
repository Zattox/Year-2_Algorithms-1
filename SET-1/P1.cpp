#include <stdexcept>
#include <unordered_set>
#include "list.h"

List::List() {
  _size = 0;
  head = nullptr;
  tail = nullptr;
}

List::List(const List& other) {
  _size = other._size;
  head = new Node(other.head->value);
  Node* cur = other.head->next;
  Node* prev = head;
  tail = head;
  while (cur != nullptr) {
    tail = new Node(cur->value);
    tail->prev = prev;
    prev->next = tail;
    cur = cur->next;
    prev = tail;
  }
}

List::List(std::vector<int> array) {
  _size = array.size();
  head = new Node(array[0]);
  Node* prev = head;
  for (int i = 1; i < (int)_size; ++i) {
    Node* cur = new Node(array[i]);
    cur->prev = prev;
    prev->next = cur;
    prev = cur;
    if (i == size() - 1) {
      tail = cur;
    }
  }
}

List::~List() {
  clear();
}

int List::front() {
  return head->value;
}


int List::back() {
  return tail->value;
}

void List::push_back(int value) {
  Node* ptr = new Node(value);
  if (tail == nullptr) {
    head = ptr;
    tail = ptr;
  } else {
    tail->next = ptr;
    ptr->prev = tail;
    tail = ptr;
  }
  ++_size;
}

void List::push_front(int value) {
  Node* ptr = new Node(value);
  if (head == nullptr) {
    head = ptr;
    tail = ptr;
  } else {
    head->prev = ptr;
    ptr->next = head;
    head = ptr;
  }
  ++_size;
}

void List::insert(Node* pos, int value) {
  if (pos == nullptr) {
    throw std::runtime_error("Incorrect position!");
  }

  int i = 1;
  auto cur = head;
  while (cur != tail && cur != pos) {
    cur = cur->next;
    ++i;
  }

  Node* ptr = new Node(value);
  if (cur->next == nullptr) {
    cur->next = ptr;
    ptr->prev = cur;
  } else {
    auto tmp = cur->next;
    cur->next = ptr;
    ptr->prev = cur;
    tmp->prev = ptr;
    ptr->next = tmp;
  }
  ++_size;
}

void List::pop_front() {
  if (head == nullptr) {
    return;
  }

  Node* ptr = head->next;
  if (ptr != nullptr) {
    ptr->prev = nullptr;
  } else {
    tail = nullptr;
  }

  delete head;
  head = ptr;
  --_size;
}

void List::pop_back() {
  if (tail == nullptr) {
    return;
  }

  Node* ptr = tail->prev;
  if (ptr != nullptr) {
    ptr->next = nullptr;
  } else {
    head = nullptr;
  }

  delete tail;
  tail = ptr;
  --_size;
}

void List::erase(Node* pos) {
  if (pos == nullptr) {
    throw std::runtime_error("Incorrect position!");
  }

  if (pos->prev != nullptr) {
    pos->prev->next = pos->next;
  } else {
    head = pos->next;
  }
  if (pos->next != nullptr) {
    pos->next->prev = pos->prev;
  } else {
    tail = pos->prev;
  }

  delete pos;
  --_size;
}

void List::clear() {
  while (_size > 0) {
    pop_back();
  }
  tail = nullptr;
}

void List::reverse() {
  if (head == nullptr || head->next == nullptr) {
    return;
  }
  std::swap(head, tail);

  Node* prev = nullptr;
  Node* cur = tail;
  while (cur != nullptr) {
    prev = cur->prev;
    cur->prev = cur->next;
    cur->next = prev;

    cur = cur->prev;
  }
}

void List::remove_duplicates() {
  std::unordered_set<int> st;
  Node* cur = head;
  while (cur != nullptr) {
    if (st.find(cur->value) == st.end()){
      st.insert(cur->value);
      cur = cur->next;
    } else {
      if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
      }
      if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
      }
      Node* tmp = cur;
      if (tmp == tail) {
        tail = cur->prev;
      }
      cur = cur->next;
      delete tmp;
      --_size;
    }
  }
}

void List::replace(int old_value, int new_value) {
  auto cur = head;
  while (cur != nullptr) {
    if (cur->value == old_value) {
      cur->value = new_value;
    }
    cur = cur->next;
  }
}

void List::merge(const List& other) {
  Node* ptr_other = other.head;
  while (ptr_other != nullptr) {
    push_back(ptr_other->value);
    ptr_other = ptr_other->next;
  }
}

bool List::check_cycle() const {
  std::unordered_set<Node*> st;

  Node* cur = head;
  while (cur != nullptr) {
    if (st.find(cur) != st.end()) {
      st.clear();
      return true;
    }
    st.insert(cur);
    cur = cur->next;
  }
  return false;
}

size_t List::size() const {
  return _size;
}

bool List::empty() const {
  return (_size == 0);
}

void List::copy(const List& other) {
  clear();
  _size = other._size;
  head = new Node(other.head->value);
  Node* cur = other.head->next;
  Node* prev = head;
  tail = head;
  while (cur != nullptr) {
    tail = new Node(cur->value);
    tail->prev = prev;
    prev->next = tail;
    cur = cur->next;
    prev = tail;
  }
}
