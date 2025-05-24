#include <bits/stdc++.h>

using namespace std;

struct Node {
  int freq;
  char ch;
  Node *left;
  Node *right;
  Node(int f, char c) : freq(f), ch(c), left(nullptr), right(nullptr) {}
};

struct Compare {
  bool operator()(Node *a, Node *b) {
    if (a->freq == b->freq) {
      return a->ch < b->ch;
    }
    return a->freq > b->freq;
  }
};

void buildCodes(Node *node, string code, map<char, string> &codes) {
  if (node == nullptr) return;
  if (node->left == nullptr && node->right == nullptr) {
    codes[node->ch] = code.empty() ? "0" : code;
  } else {
    buildCodes(node->left, code + "0", codes);
    buildCodes(node->right, code + "1", codes);
  }
}

void deleteTree(Node *node) {
  if (node == nullptr) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

int solve() {
  string s;
  getline(cin, s);

  const int ALPHABET_SIZE = 26;
  int freq[ALPHABET_SIZE] = {0};
  for (char c : s) {
    freq[c - 'a']++;
  }

  priority_queue<Node *, vector<Node *>, Compare> pq;
  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (freq[i] > 0) {
      pq.push(new Node(freq[i], 'a' + i));
    }
  }

  if (pq.size() == 1) {
    Node *root = pq.top();
    map<char, string> codes;
    codes[root->ch] = "0";
    string encoded(s.length(), '0');
    cout << 1 << " " << encoded.size() << endl;
    cout << root->ch << ": " << codes[root->ch] << endl;
    cout << encoded << endl;
    delete root;
    return 0;
  }

  while (pq.size() > 1) {
    Node *left = pq.top();
    pq.pop();
    Node *right = pq.top();
    pq.pop();
    int sum_freq = left->freq + right->freq;
    Node *parent = new Node(sum_freq, '\0');
    parent->left = left;
    parent->right = right;
    pq.push(parent);
  }

  Node *root = pq.top();

  map<char, string> codes;
  buildCodes(root, "", codes);

  string encoded = "";
  for (char c : s) {
    encoded += codes[c];
  }

  int k = codes.size();
  cout << k << " " << encoded.size() << endl;
  for (const auto &pair : codes) {
    cout << pair.first << ": " << pair.second << endl;
  }
  cout << encoded << endl;

  deleteTree(root);

  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}