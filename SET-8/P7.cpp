#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int k = 26;

struct Vertex {
  Vertex *to[k] = {nullptr};
  Vertex *suffix_link = nullptr;
  Vertex *output_link = nullptr;
  vector<int> patterns;
  int pch;
  Vertex *p;

  Vertex(int _pch = -1, Vertex *_p = nullptr) : pch(_pch), p(_p) {}
};

class AhoCorasick {
 private:
  Vertex *root;
  vector<Vertex *> all_nodes;
  vector<int> pattern_lengths;

 public:
  AhoCorasick() {
    root = new Vertex();
    all_nodes.push_back(root);
  }

  ~AhoCorasick() {
    for (Vertex *node : all_nodes) {
      delete node;
    }
  }

  void add_string(const string &s, int pattern_idx) {
    Vertex *v = root;
    for (char c : s) {
      int char_idx = c - 'a';
      if (!v->to[char_idx]) {
        v->to[char_idx] = new Vertex(char_idx, v);
        all_nodes.push_back(v->to[char_idx]);
      }
      v = v->to[char_idx];
    }
    v->patterns.push_back(pattern_idx);
    pattern_lengths.push_back(s.length());
  }

  void prepare() {
    queue<Vertex *> q;
    root->suffix_link = root;
    root->output_link = nullptr;

    for (int c = 0; c < k; c++) {
      if (root->to[c]) {
        root->to[c]->suffix_link = root;
        q.push(root->to[c]);
      }
    }

    while (!q.empty()) {
      Vertex *u = q.front();
      q.pop();

      for (int c = 0; c < k; c++) {
        if (u->to[c]) {
          Vertex *child = u->to[c];
          Vertex *temp = u->suffix_link;

          while (temp != root && !temp->to[c]) {
            temp = temp->suffix_link;
          }
          child->suffix_link = temp->to[c] ? temp->to[c] : root;

          if (!child->suffix_link->patterns.empty()) {
            child->output_link = child->suffix_link;
          } else {
            child->output_link = child->suffix_link->output_link;
          }

          q.push(child);
        }
      }
    }
  }

  void process_text(const string &text, vector<vector<int>> &occurrences) {
    Vertex *current = root;
    for (int i = 0; i < text.length(); i++) {
      int c = text[i] - 'a';

      while (current != root && !current->to[c]) {
        current = current->suffix_link;
      }
      if (current->to[c]) {
        current = current->to[c];
      } else {
        current = root;
      }

      Vertex *temp = current;
      while (temp) {
        for (int idx : temp->patterns) {
          int pos = i - pattern_lengths[idx] + 1; // 0-based
          if (pos >= 0) {
            occurrences[idx].push_back(pos + 1); // 1-based
          }
        }
        temp = temp->output_link;
      }
    }
  }
};

void solve() {
  string text;
  int n;
  cin >> text >> n;

  AhoCorasick ac;
  vector<vector<int>> occurrences(n);

  for (int i = 0; i < n; i++) {
    string pattern;
    cin >> pattern;
    ac.add_string(pattern, i);
  }

  ac.prepare();
  ac.process_text(text, occurrences);

  for (int i = 0; i < n; i++) {
    sort(occurrences[i].begin(), occurrences[i].end());
    occurrences[i].erase(unique(occurrences[i].begin(), occurrences[i].end()), occurrences[i].end());
    cout << occurrences[i].size();
    for (int pos : occurrences[i]) {
      cout << " " << pos;
    }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}