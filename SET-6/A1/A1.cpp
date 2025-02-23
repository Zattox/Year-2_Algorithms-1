#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Edge {
  int u, v, weight;
  bool operator<(const Edge& other) const {
    return weight > other.weight;
  }
};

struct DSU {
  vector<int> parent, rank;
  DSU(int n) : parent(n), rank(n, 0) {
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int x);
  bool unite(int x, int y); // Возвращает false, если цикл образовался
  bool is_bridge(Edge e, vector<Edge> &gr, int n);
};

vector<Edge> ALG_1(vector<Edge> edges, int n) {
  int m = edges.size();
  vector<Edge> gr(edges.begin(), edges.end());
  sort(gr.begin(), gr.end());

  DSU dsu(n);
  for (const auto& e : gr) {
    dsu.unite(e.u, e.v);
  }

  vector<Edge> result;
  for (int i = 0; i < m; ++i) {
    Edge e = gr[i];
    DSU temp_dsu = dsu;
    if (!temp_dsu.is_bridge(e, gr, n)) {
      // Ребро можно удалить, не добавляем его в результат
    } else {
      result.push_back(e); // Сохраняем, если удаление разрывает граф
    }
  }

  return result;
}

vector<Edge> alg2(vector<Edge> edges, int n) {
  DSU dsu(n);
  shuffle(edges.begin(), edges.end(), std::mt19937(std::random_device()()));
  vector<Edge> graph;
  for (auto e : edges) {
    if (dsu.find(e.u) != dsu.find(e.v)) { // Если добавление не создаёт цикл
      dsu.unite(e.u, e.v);
      graph.push_back(e);
    }
  }
  return graph;
}

vector<Edge> alg3(vector<Edge> edges, int n) {
  DSU dsu(n);
  shuffle(edges.begin(), edges.end(), std::mt19937(std::random_device()())); // Случайный порядок рёбер
  vector<Edge> graph;

  for (auto e : edges) {
    graph.push_back(e); // Добавляем ребро
    if (dsu.find(e.u) == dsu.find(e.v)) { // Обнаружен цикл (перед unite)
      int max_weight = INT_MIN, max_idx = -1; // Инициализация для любых весов (включая отрицательные)
      for (int j = 0; j < graph.size(); ++j) {
        int u = graph[j].u, v = graph[j].v;
        if (dsu.find(u) == dsu.find(v)) { // Ребро в цикле
          if (graph[j].weight > max_weight) {
            max_weight = graph[j].weight;
            max_idx = j;
          }
        }
      }
      if (max_idx != -1) {
        graph.erase(graph.begin() + max_idx); // Удаляем ребро с максимальным весом
      }
    } else {
      dsu.unite(e.u, e.v); // Объединяем, если нет цикла
    }
  }
  return graph;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}