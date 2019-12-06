#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>

#define FILE "cnf"

using namespace std;

typedef long long ll;

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    //    freopen(FILE".in", "r", stdin);
    //    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    const int INF = 1e9;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        g[v - 1][u - 1] = min(w, g[v - 1][u - 1]);
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << g[i][j] << ' ';
        }
        cout << '\n';
    }


    return 0;
}
