#include <iostream>
#include <vector>
#include <random>

const int MAX_LEVEL = 15;
std::mt19937 getRand(13);

struct SkipListNode {
  int value;
  std::vector<SkipListNode *> next;

  SkipListNode(int val, int level) : value(val), next(level + 1, nullptr) {}
};

class SkipList {
 private:
  int maxLevel;
  int currentLevel;
  SkipListNode *head;

  int getRandomLevel() const {
    int level = 0;
    while (getRand() % 2 == 0 && level < maxLevel) {
      level++;
    }
    return level;
  }

 public:
  int totalFindOperations = 0;

  SkipList() : maxLevel(MAX_LEVEL), currentLevel(0) {
    head = new SkipListNode(-1, maxLevel);
  }

  ~SkipList() {
    SkipListNode *current = head;
    while (current) {
      SkipListNode *temp = current;
      current = current->next[0];
      delete temp;
    }
  }

  void insert(int value) {
    std::vector<SkipListNode *> updated_nodes(maxLevel + 1, nullptr);
    SkipListNode *cur = head;
    for (int i = currentLevel; i >= 0; i--) {
      while (cur->next[i] && cur->next[i]->value < value) {
        cur = cur->next[i];
      }
      updated_nodes[i] = cur;
    }
    cur = cur->next[0];
    if (cur != nullptr && cur->value == value) {
      return;
    }

    int newLevel = getRandomLevel();
    SkipListNode *newNode = new SkipListNode(value, newLevel);
    if (newLevel > currentLevel) {
      for (int i = currentLevel + 1; i <= newLevel; ++i) {
        updated_nodes[i] = head;
      }
      currentLevel = newLevel;
    }
    for (int i = 0; i <= newLevel; ++i) {
      newNode->next[i] = updated_nodes[i]->next[i];
      updated_nodes[i]->next[i] = newNode;
    }
  }

  bool search(int value) {
    SkipListNode *cur = head;
    for (int i = currentLevel; i >= 0; i--) {
      while (cur->next[i] && cur->next[i]->value < value) {
        cur = cur->next[i];
        totalFindOperations++;
      }
      totalFindOperations++;
    }
    cur = cur->next[0];
    return (cur != nullptr && cur->value == value);
  }

  void remove(int value) {
    std::vector<SkipListNode *> updated_nodes(maxLevel + 1, nullptr);
    SkipListNode *cur = head;

    for (int i = currentLevel; i >= 0; i--) {
      while (cur->next[i] && cur->next[i]->value < value) {
        cur = cur->next[i];
      }
      updated_nodes[i] = cur;
    }

    cur = cur->next[0];
    if (cur == nullptr || cur->value != value) {
      return;
    }

    for (int i = 0; i <= currentLevel; ++i) {
      if (updated_nodes[i]->next[i] != cur) break;
      updated_nodes[i]->next[i] = cur->next[i];
    }

    while (currentLevel > 0 && head->next[currentLevel] == nullptr) {
      currentLevel--;
    }

    delete cur;
  }

  void printList() {
    for (int i = 0; i <= currentLevel; ++i) {
      std::cout << "Level " << i << ": ";
      SkipListNode *node = head->next[i];
      while (node) {
        std::cout << node->value << " -> ";
        node = node->next[i];
      }
      std::cout << "None" << std::endl;
    }
  }
};