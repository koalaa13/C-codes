#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

#define FILE "components"

using namespace std;

const int N = 111111;
vector<vector<int>> g(N);
bitset<N> used;
vector<int> comp(N);

void dfs(int v, int cur_col) {
    used[v] = true;
    comp[v] = cur_col;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to, cur_col);
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
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
        g[u - 1].push_back(v - 1);
    }
    int col = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, col++);
        }
    }
    cout << col << '\n';
    for_each(comp.begin(), comp.begin() + n, [](int v) { cout << v + 1 << ' '; });
    return 0;
}
