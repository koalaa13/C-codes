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
    int n, s, f;
    cin >> n >> s >> f;
    s--;
    f--;
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    const ll INF = 2e18;
    vector<ll> d(n, INF);
    d[s] = 0;
    vector<bool> used(n);
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || d[v] > d[j])) {
                v = j;
            }
        }
        used[v] = true;
        for (int j = 0; j < n; ++j) {
            if (g[v][j] != -1) {
                d[j] = min(d[j], d[v] + g[v][j]);
            }
        }
    }
    cout << (d[f] == INF ? -1 : d[f]);

    return 0;
}
