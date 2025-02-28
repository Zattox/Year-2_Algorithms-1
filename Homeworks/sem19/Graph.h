#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
 private:
  int n; // Maximum vertex index (number of vertices = n + 1)
  std::vector<bool> exists; // Tracks existing vertices
  std::vector<std::vector<int>> edges; // Adjacency list representation

  // Depth-First Search to traverse the graph
  void dfs(int v, std::vector<bool> &visited) {
    visited[v] = true;
    for (int neighbor : edges[v]) {
      if (exists[neighbor] && !visited[neighbor]) {
        dfs(neighbor, visited);
      }
    }
  }

 public:
  // Constructor: initializes the graph with a given maximum vertex index
  Graph(int maxVertex = 0) : n(maxVertex) {
    edges.resize(maxVertex + 1);
    exists.resize(maxVertex + 1, false);
  }

  // Adds an undirected edge between vertices u and v (including loops)
  void addEdge(int u, int v) {
    if (u > n || v > n || u < 0 || v < 0) {
      throw std::out_of_range("Vertex index exceeds maximum allowed");
    }
    exists[u] = true;
    exists[v] = true;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  // Checks if the graph is connected
  bool isConnected() {
    if (n == 0) {
      return true; // Empty graph is considered connected
    }

    // Find the first existing vertex
    int start = -1;
    for (int i = 0; i <= n; ++i) {
      if (exists[i]) {
        start = i;
        break;
      }
    }

    std::vector<bool> visited(n + 1, false);
    dfs(start, visited);

    // Check all existing vertices
    for (int i = 0; i <= n; ++i) {
      if (exists[i] && !visited[i]) {
        return false; // If any existing vertex is unvisited, the graph is disconnected
      }
    }
    return true;
  }

  // Checks if the graph is Eulerian (has an Eulerian cycle or path)
  bool isEulerian() {
    if (n == 0) {
      std::cout << "Graph is empty\n";
      return false; // An empty graph is not Eulerian
    }

    if (!isConnected()) {
      std::cout << "Graph is not connected\n";
      return false; // A disconnected graph cannot be Eulerian
    }

    int oddCount = 0; // Count of vertices with odd degree
    for (int i = 0; i <= n; ++i) {
      if (exists[i]) {
        size_t degree = edges[i].size(); // Degree = number of edges (including loops)
        if (degree % 2 != 0) {
          ++oddCount;
        }
      }
    }

    if (oddCount == 0) {
      std::cout << "Eulerian Cycle\n";
      return true; // All vertices have even degree: Eulerian cycle exists
    } else if (oddCount == 2) {
      std::cout << "Eulerian Path\n";
      return true; // Exactly two vertices have odd degree: Eulerian path exists
    } else {
      std::cout << "Not Eulerian\n";
      return false; // More than two vertices have odd degree: not Eulerian
    }
  }
};

#endif // GRAPH_H