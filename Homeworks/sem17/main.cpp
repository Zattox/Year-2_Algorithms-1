#include "Graph.h"
#include <string>

using namespace std;

void runTest(int n, vector<pair<int, int>> arr, string text) {
  cout << "\n" << text << "\n";
  Graph gr(n);
  // Add edges
  for (auto el : arr) {
    gr.addEdge(el.first, el.second);
  }
  gr.isEulerian();
}

int main() {
  // Test 1: Empty graph
  runTest(0, {},
          "Test 1: Empty Graph");

  // Test 2: Eulerian Cycle (Square)
  runTest(3, {{0, 1}, {1, 2}, {2, 3}, {3, 0}},
          "Test 2: Eulerian Cycle");

  // Test 3: Eulerian Path
  runTest(3, {{0, 1}, {1, 2}, {2, 3}},
          "Test 3: Eulerian Path");

  // Test 4: Disconnected graph
  runTest(3, {{0, 1}, {2, 3}},
          "Test 4: Disconnected Graph");

  // Test 5: Star graph (4 leaves)
  runTest(4, {{0, 1}, {0, 2}, {0, 3}, {0, 4}},
          "Test 5: Star Graph");

  // Test 6: Complete K4
  runTest(3, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}},
          "Test 6: Complete K4");

  // Test 7: Graph with multiple components
  runTest(5, {{0, 1}, {1, 2}, {2, 0}, {3, 4}},
          "Test 7: Graph with Multiple Components");

  // Test 8: Graph with a loop
  runTest(1, {{0, 0}},
          "Test 8: Graph with a Loop");

  // Test 9: Eulerian Cycle with multiple edges
  runTest(2, {{0, 1}, {0, 1}, {1, 2}, {1, 2}, {2, 0}, {2, 0}},
          "Test 9: Eulerian Cycle with Multiple Edges");

  // Test 10: Graph with negative vertex indices
  try {
    runTest(2, {{-1, 0}, {0, 1}},
            "Test 10: Graph with Negative Vertex Indices");
  } catch (const std::out_of_range &e) {
    std::cout << "Caught exception: " << e.what() << "\n";
  }

  return 0;
}