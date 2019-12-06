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

#define FILE "cnf"

typedef long long ll;

using namespace std;

const int N = 11111;
vector<vector<int>> g(N);
bitset<N> used;

void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
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

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    vector<int> free_ls;
    for (int i = 0; i < n; ++i) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            int v;
            cin >> v;
            edges.emplace_back(i, v - 1 + n);
        }
    }
    multiset<pair<int, int>> ms;
    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        if (v != 0) {
            v--;
            g[v + n].push_back(i);
            ms.insert({i, v + n});
        } else {
            free_ls.push_back(i);
        }
    }
    for (pair<int, int> e : edges) {
        if (ms.find(e) == ms.end()) {
            g[e.first].push_back(e.second);
        }
    }
    for (int v : free_ls) {
        dfs(v);
    }
    vector<int> l_m, r_p;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            l_m.push_back(i);
        }
    }
    for (int i = n; i < n + m; ++i) {
        if (used[i]) {
            r_p.push_back(i);
        }
    }
    cout << l_m.size() + r_p.size() << '\n';
    sort(l_m.begin(), l_m.end());
    sort(r_p.begin(), r_p.end());
    cout << l_m.size() << ' ';
    for (int v : l_m) {
        cout << v + 1 << ' ';
    }
    cout << '\n' << r_p.size() << ' ';
    for (int v : r_p) {
        cout << v + 1 - n << ' ';
    }

    return 0;
}
