#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

#define FILE "bipartite"

using namespace std;

const int N = 111111;
vector<vector<int>> g(N);
vector<int> cols(N, -1);
int timer = 0;

void dfs(int v, int col = 0) {
    cols[v] = col;
    for (int to : g[v]) {
        if (cols[to] == -1) {
            dfs(to, col ^ 1);
        } else {
            if (cols[to] == cols[v]) {
                cout << "NO";
                exit(0);
            }
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
    for (int i = 0; i < n; ++i) {
        if (cols[i] == -1) {
            dfs(i);
        }
    }
    cout << "YES";
    return 0;
}
