#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

#define FILE "points"

using namespace std;

const int N = 111111;
vector<int> up(N), tin(N), col(N);
set<int> cvs;
vector<vector<pair<int, int>>> g(N);
int timer = 0;

void dfs(int v, int par = -1) {
    int children = 0;
    col[v] = 1;
    tin[v] = up[v] = timer++;
    for (auto to : g[v]) {
        if (col[to.first] == 1 && to.first != par) {
            up[v] = min(up[v], tin[to.first]);
        }
        if (col[to.first] == 0) {
            dfs(to.first, to.second);
            up[v] = min(up[v], up[to.first]);
            if (up[to.first] >= tin[v] && par != -1) {
                cvs.insert(v);
            }
            ++children;
        }
    }
    if (par == -1 && children > 1) {
        cvs.insert(v);
    }
    col[v] = 2;
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
        g[v - 1].push_back({u - 1, i});
        g[u - 1].push_back({v - 1, i});
    }
    for (int i = 0; i < n; ++i) {
        if (col[i] == 0) {
            dfs(i);
        }
    }
    cout << cvs.size() << '\n';
    for_each(cvs.begin(), cvs.end(), [](int v) { cout << v + 1 << ' '; });

    return 0;
}
