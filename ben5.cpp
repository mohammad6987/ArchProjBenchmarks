#include <bits/stdc++.h>
#include <math.h>
#include <cstdio>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 1000;
    long double result_t = -1;

    // Seed the random number generator with the current time
    srand(time(0));

    vector<pair<int, pair<int, int>>> information(n);

    // Generate random inputs
    for (int i = 0; i < n; i++) {
        int r = rand() % 200 + 1; 
        int a = rand() % 200 + 1; 
        int b = rand() % 200 + 1; 

        information[i].first = b;
        information[i].second.first = r;
        information[i].second.second = a;
    }

    // Sort the information based on 'b'
    sort(information.begin(), information.end());

    // Find the smallest time 't' where the conditions are met
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (information[i].second.second > information[j].second.second) {
                int delta_x = information[j].first - information[i].first;
                long double t = (delta_x -
                                 2 * sqrt(information[i].second.first * information[j].second.first)) /
                                (long double)(information[i].second.second - information[j].second.second);
                if (t >= 0 && (t <= result_t || result_t < 0)) {
                    result_t = t;
                }
            }
        }
    }

    if (result_t < 0) {
        printf("Collision-Free System");
    } else {
        printf("%.2Lf", result_t);
    }

    return 0;
}

