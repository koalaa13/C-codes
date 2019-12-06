#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "cond"

using namespace std;

const int N = 111111;
vector<vector<int>> g(N), rev_g(N);
bitset<N> used;
vector<int> order, comp(N);

void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    order.push_back(v);
}

void rev_dfs(int v, int cur_col) {
    used[v] = true;
    comp[v] = cur_col;
    for (int to : rev_g[v]) {
        if (!used[to]) {
            rev_dfs(to, cur_col);
        }
    }
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    freopen(FILE".in", "r", stdin);
    freopen(FILE".out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
        rev_g[u - 1].push_back(v - 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    used.reset();
    int cur_col = 0;
    for (int i = n - 1; i >= 0; --i) {
        int v = order[i];
        if (!used[v]) {
            rev_dfs(v, cur_col++);
        }
    }
    cout << cur_col << '\n';
    for (int i = 0; i < n; ++i) {
        cout << comp[i] + 1 << ' ';
    }
    return 0;
}
