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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        g[v - 1].push_back({w, u - 1});
        g[u - 1].push_back({w, v - 1});
    }
    const int INF = 2e9;
    vector<int> d(n, INF);
    d[0] = 0;
    set<pair<int, int>> q;
    q.insert({d[0], 0});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (pair<int, int> e : g[v]) {
            if (d[e.second] > d[v] + e.first) {
                q.erase({d[e.second], e.second});
                d[e.second] = d[v] + e.first;
                q.insert({d[e.second], e.second});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << ' ';
    }

    return 0;
}
