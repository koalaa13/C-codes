#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
#include <cmath>

#define FILE "cnf"

using namespace std;

typedef long long ll;
typedef long double ld;

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    //    freopen(FILE".in", "r", stdin);
    //    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);

    const int INF = 1e9;
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n)), next(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
            next[i][j] = j;
        }
    }
    for (int i = 0; i < n; ++i) {
        g[i][i] = min(0, g[i][i]);
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (g[i][k] != INF && g[k][j] != INF) {
                    int new_d = g[i][k] + g[k][j];
                    if (new_d < g[i][j]) {
                        g[i][j] = max(-INF, new_d);
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (g[i][i] < 0) {  // found negative cycle
                vector<int> path;
                path.push_back(i);
                int v = next[i][i];
                while (v != i) {
                    path.push_back(v);
                    v = next[v][i];
                }
                path.push_back(i);
                cout << "YES\n" << path.size() << '\n';
                for (int p : path) {
                    cout << p + 1 << ' ';
                }
                return 0;
            }
        }
    }
    cout << "NO";

    return 0;
}
