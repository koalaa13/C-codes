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

struct edge {
    int v, u;
    ll w;
};

const ll INF = 5e18;
const int N = 2222;
vector<vector<int>> g(N);
bitset<N> used;

void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    //    freopen(FILE".in", "r", stdin);
    //    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);

    int n, m, s;
    cin >> n >> m >> s;
    s--;
    vector<edge> es(m);
    vector<ll> d(n, INF);
    d[s] = 0;
    for (int i = 0; i < m; ++i) {
        cin >> es[i].v >> es[i].u >> es[i].w;
        es[i].v--;
        es[i].u--;
        g[es[i].v].push_back(es[i].u);
    }
    vector<int> on_negative_cycle;
    for (int i = 0; i < n; ++i) {
        for (edge e : es) {
            if (d[e.v] < INF) {
                if (d[e.v] + e.w < d[e.u]) {
                    d[e.u] = max(-INF, d[e.v] + e.w);
                    if (i == n - 1) {
                        on_negative_cycle.push_back(e.u);
                    }
                }
            }
        }
    }
    for (int v : on_negative_cycle) {
        if (!used[v]) {
            dfs(v);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            cout << "-\n";
        } else {
            if (d[i] < INF) {
                cout << d[i] << '\n';
            } else {
                cout << "*\n";
            }
        }
    }

    return 0;
}
