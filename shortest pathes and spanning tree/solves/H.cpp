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
    const int N = 22222;
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
    dsu d;
    vector<edge> es(m);
    for (int i = 0; i < m; ++i) {
        cin >> es[i].v >> es[i].u >> es[i].w;
        es[i].v--;
        es[i].u--;
    }
    ll ans = 0;
    sort(es.begin(), es.end());
    for (edge e : es) {
        if (d.get(e.v) != d.get(e.u)) {
            ans += (ll) e.w;
            d.join(e.v, e.u);
        }
    }
    cout << ans;
    return 0;
}
