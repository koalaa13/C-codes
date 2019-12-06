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

struct dsu {
    const int N = 1111;
    int *par;
    int *sz;

    dsu() {
        par = new int[N];
        sz = new int[N];
        for (int i = 0; i < N; ++i) {
            sz[i] = 1;
            par[i] = i;
        }
    }

    ~dsu() {
        delete[] par;
        delete[] sz;
    }

    int get(int v) {
        if (par[v] != v) {
            par[v] = get(par[v]);
        }
        return par[v];
    }

    void join(int v, int u) {
        v = get(v);
        u = get(u);
        if (v == u) {
            return;
        }
        if (sz[v] > sz[u]) {
            par[u] = v;
            sz[v] += sz[u];
        } else {
            par[v] = u;
            sz[u] += sz[v];
        }
    }
};

struct edge {
    int v, u, w;

    friend bool operator<(edge const &a, edge const &b) {
        return a.w < b.w;
    }
};

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
    vector<edge> es(m);
    for (int i = 0; i < m; ++i) {
        cin >> es[i].v >> es[i].u >> es[i].w;
        es[i].v--;
        es[i].u--;
    }
    const ll INF = 2e18;
    ll ans = INF;
    sort(es.begin(), es.end());
    for (int i = 0; i < m; ++i) {
        edge max_edge = es[i];
        dsu d;
        int mn = max_edge.w;
        d.join(max_edge.v, max_edge.u);
        for (int j = i - 1; j >= 0; --j) {
            edge cur_edge = es[j];
            if (d.get(cur_edge.v) != d.get(cur_edge.u)) {
                d.join(cur_edge.v, cur_edge.u);
                mn = cur_edge.w;
            }
        }
        int p = d.get(0);
        bool flag = true;
        for (int j = 1; j < n; ++j) {
            flag &= p == d.get(j);
        }
        if (flag) {
            ans = min(ans, (ll)max_edge.w - (ll)mn);
        }
    }
    if (ans == INF) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << ans;
    }
    return 0;
}
