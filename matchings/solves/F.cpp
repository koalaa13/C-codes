#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <stack>
#include <map>
#include <cassert>
#include <unordered_map>

#define FILE "cnf"

typedef long long ll;
typedef unsigned int ui;

using namespace std;

const int N = 4444;
vector<vector<int>> g(N), rev_g(N);
vector<int> order, comp(N);
bitset<N> used;

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
    //    freopen(FILE".in", "r", stdin);
    //    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> connect(n);
    for (int i = 0; i < n; ++i) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            int v;
            cin >> v;
            connect[i].push_back(v - 1);
        }
    }
    vector<int> matching(n);
    for (int i = 0; i < n; ++i) {
        cin >> matching[i];
        matching[i]--;
    }
    for (int i = 0; i < n; ++i) {
        for (int j : connect[i]) {
            if (j == matching[i]) {
                g[j + n].push_back(i);
                rev_g[i].push_back(j + n);
            } else {
                g[i].push_back(j + n);
                rev_g[j + n].push_back(i);
            }
        }
    }
    for (int i = 0; i < 2 * n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    int cur_col = 0;
    used.reset();
    for (int i = 2 * n - 1; i >= 0; --i) {
        int v = order[i];
        if (!used[v]) {
            rev_dfs(v, cur_col++);
        }
    }
    vector<vector<int>> ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j : connect[i]) {
            if (comp[i] == comp[j + n]) {
                ans[i].push_back(j);
            }
        }
        if (comp[i] != comp[matching[i] + n]) {
            ans[i].push_back(matching[i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i].size() << ' ';
        for (int j : ans[i]) {
            cout << j + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}
