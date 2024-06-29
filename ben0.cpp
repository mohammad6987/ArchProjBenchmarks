// tsp_benchmark.cpp
#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

vector<vector<int>> generateRandomDistanceMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                matrix[i][j] = rand() % 1000 + 1; // Random distances between 1 and 100
            } else {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

int tsp(int pos, int mask, vector<vector<int>>& dist, vector<vector<int>>& dp) {
    int n = dist.size();
    if (mask == (1 << n) - 1) {
        return dist[pos][0]; // Return to start
    }
    if (dp[pos][mask] != -1) {
        return dp[pos][mask];
    }
    int res = numeric_limits<int>::max();
    for (int city = 0; city < n; ++city) {
        if (!(mask & (1 << city))) {
            res = min(res, dist[pos][city] + tsp(city, mask | (1 << city), dist, dp));
        }
    }
    return dp[pos][mask] = res;
}

int main() {
    srand(time(0));
    const int numCities = 12;

    vector<vector<int>> distanceMatrix = generateRandomDistanceMatrix(numCities);
    vector<vector<int>> dp(numCities, vector<int>((1 << numCities), -1));

    clock_t start = clock();
    int minCost = tsp(0, 1, distanceMatrix, dp);
    clock_t end = clock();

    // Print execution time (can be disabled for benchmarks without output)
    // cout << "TSP time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds." << endl;

    return 0;
}

