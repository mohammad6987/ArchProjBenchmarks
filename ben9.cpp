// dijkstra_benchmark.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

struct Edge {
    int to;
    int weight;
};

vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    const int INF = numeric_limits<int>::max();
    vector<int> dist(graph.size(), INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int weight = e.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

vector<vector<Edge>> generateRandomGraph(int numVertices, int numEdges) {
    vector<vector<Edge>> graph(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        int u = rand() % numVertices;
        int v = rand() % numVertices;
        int weight = rand() % 1000 + 1; // Random weights between 1 and 100
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight}); // Assuming undirected graph
    }
    return graph;
}

int main() {
    srand(time(0));

    const int numVertices = 1000;
    const int numEdges = 5000;

    vector<vector<Edge>> graph = generateRandomGraph(numVertices, numEdges);
    int startVertex = rand() % numVertices;

    clock_t start = clock();
    vector<int> distances = dijkstra(graph, startVertex);
    clock_t end = clock();

    // Print execution time (can be disabled for benchmarks without output)
    // cout << "Dijkstra's algorithm time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds." << endl;

    return 0;
}

