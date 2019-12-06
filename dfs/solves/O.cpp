#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "chip"

using namespace std;

const int N = 55555;
int n;
vector<vector<int>> g(N * 2), rev_g(N * 2);
vector<int> wire_cols(N), id_wires(N * 2), comp(N * 2), order;
bitset<2 * N> used;

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
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> wire_cols[i];
    }
    vector<pair<int, int>> f_and_s(n);
    vector<bool> was(n);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> id_wires[i];
        id_wires[i]--;
        was[id_wires[i]] ? f_and_s[id_wires[i]].second = i : f_and_s[id_wires[i]].first = i;
        was[id_wires[i]] = true;
    }
    for (int cur = 0; cur < 2 * n; ++cur) {
        int prev = (cur - 1 + 2 * n) % (2 * n);
        int next = (cur + 1) % (2 * n);
        int prev_wire = id_wires[prev];
        int cur_wire = id_wires[cur];
        int next_wire = id_wires[next];
        if (wire_cols[prev_wire] == wire_cols[cur_wire]) {
            int wire1_vertex = 2 * prev_wire + (prev == f_and_s[prev_wire].second), wire2_vertex =
                    2 * cur_wire + (cur == f_and_s[cur_wire].second);
            g[wire1_vertex].push_back(wire2_vertex ^ 1);
            g[wire2_vertex].push_back(wire1_vertex ^ 1);
            rev_g[wire2_vertex ^ 1].push_back(wire1_vertex);
            rev_g[wire1_vertex ^ 1].push_back(wire2_vertex);
        }
        if (wire_cols[cur_wire] == wire_cols[next_wire]) {
            int wire1_vertex = 2 * cur_wire + (cur == f_and_s[cur_wire].second), wire2_vertex =
                    2 * next_wire + (next == f_and_s[next_wire].second);
            g[wire1_vertex].push_back(wire2_vertex ^ 1);
            g[wire2_vertex].push_back(wire1_vertex ^ 1);
            rev_g[wire2_vertex ^ 1].push_back(wire1_vertex);
            rev_g[wire1_vertex ^ 1].push_back(wire2_vertex);
        }
    }
    for (int i = 0; i < 2 * n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    used.reset();
    int cur_col = 0;
    for (int i = 2 * n - 1; i >= 0; --i) {
        int v = order[i];
        if (!used[v]) {
            rev_dfs(v, cur_col++);
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < 2 * n; i += 2) {
        if (comp[i] == comp[i + 1]) {
            cout << "NO";
            return 0;
        }
        ans[i / 2] = comp[i] > comp[i + 1] ? f_and_s[i / 2].first : f_and_s[i / 2].second;
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << ' ';
    }

    return 0;
}
