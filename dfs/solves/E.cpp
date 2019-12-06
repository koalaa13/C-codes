#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

#define FILE "cycle"

using namespace std;

const int N = 111111;
vector<vector<int>> g(N);
vector<int> col(N);
stack<int> vs;

void dfs(int v) {
    col[v] = 1;
    vs.push(v);
    for (int to : g[v]) {
        if (col[to] == 1) {
            cout << "YES\n";
            vector<int> ans;
            while (vs.top() != to) {
                ans.push_back(vs.top() + 1);
                vs.pop();
            }
            ans.push_back(to + 1);
            for_each(ans.rbegin(), ans.rend(), [](int v) { cout << v << ' '; });
            exit(0);
        }
        if (col[to] == 0) {
            dfs(to);
        }
    }
    col[v] = 2;
    vs.pop();
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
        if (col[i] == 0) {
            dfs(i);
        }
    }
    cout << "NO";
    return 0;
}
