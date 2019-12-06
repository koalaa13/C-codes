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

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
//    freopen(FILE".in", "r", stdin);
//    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
        g[u - 1].push_back(v - 1);
    }
    const int INF = 2e9;
    queue<int> q;
    vector<int> d(n, INF);
    d[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[v] + 1 < d[to]) {
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << ' ';
    }

    return 0;
}
