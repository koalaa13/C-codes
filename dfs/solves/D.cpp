#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "game"

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
    int n, m, s;
    cin >> n >> m >> s;
    s--;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
    }
    dfs(s);
    vector<bool> dp(n);  // 0 - lost, 1 - win
    for (int v : order) {
        if (g[v].empty()) {
            dp[v] = false;
        } else {
            bool flag = false;
            for (int to : g[v]) {
                if (!dp[to]) {
                    flag = true;
                }
            }
            dp[v] = flag;
        }
    }
    if (dp[s]) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
    return 0;
}
