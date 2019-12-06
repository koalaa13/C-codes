#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stack>

#define FILE "biconv"

using namespace std;

const int N = 222222;
vector<int> up(N), tin(N), col(N), comp(N);
vector<vector<pair<int, int>>> g(N);
int timer = 0, cur_col = 0;
stack<int> st;

void dfs(int v, int par = -1) {
    col[v] = 1;
    tin[v] = up[v] = timer++;
    for (auto to : g[v]) {
        if (to.second == par || col[to.first] == 2) {
            continue;
        }
        st.push(to.second);
        if (col[to.first] == 1) {
            up[v] = min(up[v], tin[to.first]);
        }
        if (col[to.first] == 0) {
            dfs(to.first, to.second);
            up[v] = min(up[v], up[to.first]);
            if (up[to.first] >= tin[v]) {
                while (st.top() != to.second) {
                    comp[st.top()] = cur_col;
                    st.pop();
                }
                comp[st.top()] = cur_col++;
                st.pop();
            }
        }
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
    while (!st.empty()) {
        comp[st.top()] = cur_col;
        st.pop();
    }
    cout << cur_col << '\n';
    for (int i = 0; i < m; ++i) {
        cout << comp[i] + 1 << ' ';
    }

    return 0;
}
