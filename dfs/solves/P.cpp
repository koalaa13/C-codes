#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "cnf"

using namespace std;

const int N = 222;
int n, m;
vector<vector<int>> g(N), rev_g(N);
vector<int> order, comp(N);
bitset<N> used;

void add_edge(int a, int b) {
    g[-a + n].push_back(b + n);
    g[-b + n].push_back(a + n);
    rev_g[b + n].push_back(-a + n);
    rev_g[a + n].push_back(-b + n);
}

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
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b);
        add_edge(b, c);
        add_edge(a, c);
    }
    for (int i = 0; i <= 2 * n; ++i) {
        if (i != n && !used[i]) {
            dfs(i);
        }
    }
    used.reset();
    int cur_col = 0;
    for (int i = order.size() - 1; i >= 0; --i) {
        int v = order[i];
       if (!used[v]) {
           rev_dfs(v, cur_col++);
       }
    }
    vector<int> ans(n);
    for (int i = 1; i <= n; ++i) {
        if (comp[i + n] == comp[-i + n]) {
            cout << "NO";
            return 0;
        }
        ans[i - 1] = comp[i + n] > comp[-i + n] ? i : -i;
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }

    return 0;
}
