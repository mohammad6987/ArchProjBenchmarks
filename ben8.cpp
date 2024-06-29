// bfs_benchmark.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

struct Graph {
    int vertices;
    std::vector<std::vector<int>> adjList;

    Graph(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
};

void bfs(const Graph& g, int start) {
    std::vector<bool> visited(g.vertices, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : g.adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    const int numVertices = 2500; // Number of vertices
    const int numEdges = 7500;    // Number of edges

    // Seed for random number generation
    std::srand(std::time(nullptr));

    Graph g(numVertices);

    // Generate random edges
    for (int i = 0; i < numEdges; ++i) {
        int u = std::rand() % numVertices;
        int v = std::rand() % numVertices;
        g.addEdge(u, v);
    }

    // Choose a random starting point for BFS
    int start = std::rand() % numVertices;

    // Measure time for BFS
    clock_t startClock = clock();
    bfs(g, start);
    clock_t endClock = clock();

    // Print execution time (can be disabled for benchmarks without output)
    // std::cout << "BFS time: " << static_cast<double>(endClock - startClock) / CLOCKS_PER_SEC << " seconds." << std::endl;

    return 0;
}

