#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

#define FILE "hamiltonian"

using namespace std;

const int N = 111111;
vector<vector<int>> g(N);
bitset<N> used;
vector<int> order;

void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    order.push_back(v);
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
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    vector<int> dp(n, 1);
    for (int v : order) {
        for (int to : g[v]) {
            dp[v] = max(dp[v], dp[to] + 1);
        }
    }
    for (int v = 0; v < n; ++v) {
        if (dp[v] == n) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
