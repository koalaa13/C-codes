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

const int N = 155;
vector<vector<bool>> connect(N, vector<bool>(N));
vector<vector<int>> g(2 * N);
vector<int> match(N);
bitset<2 * N> used;
int n, m;

bool kuhn_dfs(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int i = 0; i < m; ++i) {
        if (connect[v][i]) {
            if (match[i] == -1 || kuhn_dfs(match[i])) {
                match[i] = v;
                return true;
            }
        }
    }
    return false;
}

void kuhn() {
    for (int i = 0; i < m; ++i) {
        match[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        used.reset();
        kuhn_dfs(i);
    }
}

void find_parts(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            find_parts(to);
        }
    }
}

void solve() {
    cin >> n >> m;
    set<int> ss;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            connect[i][j] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        ss.insert(i);
        while (true) {
            int v;
            cin >> v;
            if (v == 0) {
                break;
            }
            connect[i][v - 1] = false;
        }
    }
    kuhn();
    multiset<pair<int, int>> matching;
    for (int i = 0; i < m; ++i) {
        if (match[i] != -1) {
            matching.insert({match[i], i});
            ss.erase(match[i]);
        }
    }
    for (int i = 0; i < n + m; ++i) {
        g[i].clear();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (connect[i][j]) {
                if (matching.find({i, j}) == matching.end()) {
                    g[i].push_back(j + n);
                } else {
                    g[j + n].push_back(i);
                }
            }
        }
    }
    used.reset();
    for (int v : ss) {
        find_parts(v);
    }
    vector<int> l_p, r_m;
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            l_p.push_back(i);
        }
    }
    for (int i = n; i < n + m; ++i) {
        if (!used[i]) {
            r_m.push_back(i);
        }
    }
    sort(l_p.begin(), l_p.end());
    sort(r_m.begin(), r_m.end());
    cout << l_p.size() + r_m.size() << '\n' << l_p.size() << ' ' << r_m.size() << '\n';
    for (int v : l_p) {
        cout << v + 1 << ' ';
    }
    cout << '\n';
    for (int v : r_m) {
        cout << v + 1 - n << ' ';
    }
    cout << "\n\n";
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    //    freopen(FILE".in", "r", stdin);
    //    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }

    return 0;
}
