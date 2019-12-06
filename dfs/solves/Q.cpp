#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "truth"

using namespace std;

const int N = 55555;
int n, m;
vector<vector<pair<int, int>>> g(N * 2), rev_g(N * 2);
vector<int> comp(N * 2), order;
bitset<2 * N> used;

void dfs(int v, int mid) {
    used[v] = true;
    for (pair<int, int> to : g[v]) {
        if (!used[to.first] && to.second < mid) {
            dfs(to.first, mid);
        }
    }
    order.push_back(v);
}

void rev_dfs(int v, int cur_col, int mid) {
    used[v] = true;
    comp[v] = cur_col;
    for (pair<int, int> to : rev_g[v]) {
        if (!used[to.first] && to.second < mid) {
            rev_dfs(to.first, cur_col, mid);
        }
    }
}

void add_edge(int v, int u, int id) {
    g[v].push_back({u, id});
    rev_g[u].push_back({v, id});
}

bool can(int mid) {
    int col = 0;
    used.reset();
    order.clear();
    for (int i = 0; i < 2 * n; ++i) {
        if (!used[i]) {
            dfs(i, mid);
        }
    }
    used.reset();
    for (int i = 2 * n - 1; i >= 0; --i) {
        int v = order[i];
        if (!used[v]) {
            rev_dfs(v, col++, mid);
        }
    }
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        flag &= comp[2 * i] != comp[2 * i + 1];
    }
    return flag;
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    freopen(FILE".in", "r", stdin);
    freopen(FILE".out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        char c;
        cin >> v >> u >> c;
        v--;
        u--;
        if (c == 'L') {
            add_edge(v * 2, u * 2 + 1, i);
            add_edge(v * 2 + 1, u * 2, i);
            add_edge(u * 2 + 1, v * 2, i);
            add_edge(u * 2, v * 2 + 1, i);
        } else {
            add_edge(v * 2, u * 2, i);
            add_edge(v * 2 + 1, u * 2 + 1, i);
            add_edge(u * 2, v * 2, i);
            add_edge(u * 2 + 1, v * 2 + 1, i);
        }
    }
    int l = 0, r = m;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (can(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << (can(r) ? r : l);

    return 0;
}
