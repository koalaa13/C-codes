#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "dfs"

using namespace std;

const int N = 333;
vector<set<int>> g(N);
vector<int> dep(N), tin(N), tout(N);
vector<pair<int, int>> ans_edges;
int timer = 0;

void dfs(int v, int d = 0, int par = -1) {
    dep[v] = d;
    tin[v] = timer++;
    for (int to : g[v]) {
        if (to != par) {
            dfs(to, d + 1, v);
        }
    }
    tout[v] = timer++;
}

bool is_par(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

bool check(int v, int u) {
    for (int to : g[v]) {
        if (is_par(to, u)) {
            v = to;
            break;
        }
    }
    return v < u;
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    freopen(FILE".in", "r", stdin);
    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    int n, l;
    cin >> n >> l;
    vector<int> arr(l);
    vector<vector<int>> inds(n);
    for (int i = 0; i < l; ++i) {
        cin >> arr[i];
        arr[i]--;
        inds[arr[i]].push_back(i);
    }
    vector<pair<int, int>> forest;
    for (int i = 0;;) {
        if (i < l) {
            forest.emplace_back(*inds[arr[i]].begin(), *inds[arr[i]].rbegin());
            i = forest.back().second + 1;
        } else {
            break;
        }
    }
    vector<bool> used(n);
    vector<int> roots;
    for (pair<int, int> p : forest) {
        int v = arr[p.first];
        roots.push_back(v);
        used[v] = true;
        for (int i = p.first + 1; i <= p.second; ++i) {
            if (!used[arr[i]]) {
                g[v].insert(arr[i]);
                ans_edges.emplace_back(v, arr[i]);
            }
            v = arr[i];
            used[v] = true;
        }
    }
    for (int root : roots) {
        dfs(root);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (is_par(i, j) && dep[j] - dep[i] > 1 && check(i, j)) {
                ans_edges.emplace_back(i, j);
            }
        }
    }
    cout << ans_edges.size() << '\n';
    for (pair<int, int> e : ans_edges) {
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
    }

    return 0;
}
