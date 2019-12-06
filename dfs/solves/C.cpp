#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "shortpath"

using namespace std;

const int N = 111111;
vector<vector<pair<int, int>>> g(N);
bitset<N> used;
vector<int> order;

void dfs(int v) {
    used[v] = true;
    for (pair<int, int> to : g[v]) {
        if (!used[to.first]) {
            dfs(to.first);
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
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--;
    t--;
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        g[v - 1].push_back({u - 1, w});
    }
    dfs(s);
    if (!used[t]) {
        cout << "Unreachable";
        return 0;
    }
    const int INF = 2e9;
    vector<int> dp(n, INF);
    dp[t] = 0;
    for (int v : order) {
        for (auto e : g[v]) {
            dp[v] = min(dp[v], dp[e.first] + e.second);
        }
    }
    cout << dp[s];

    return 0;
}
