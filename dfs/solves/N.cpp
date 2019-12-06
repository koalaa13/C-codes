#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "avia"

using namespace std;

const int N = 1111;
int n;
vector<vector<int>> g(N, vector<int>(N));
vector<int> order;
bitset<N> used;

void dfs(int v, int mid) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if (!used[i] && g[v][i] <= mid) {
            dfs(i, mid);
        }
    }
    order.push_back(v);
}

void rev_dfs(int v, int mid) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if (!used[i] && g[i][v] <= mid) {
            rev_dfs(i, mid);
        }
    }
}

inline bool can(int mid) {
    int col = 0;
    used.reset();
    order.clear();
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, mid);
        }
    }
    used.reset();
    for (int i = order.size() - 1; i >= 0; --i) {
        int v = order[i];
        if (!used[v]) {
            rev_dfs(v, mid);
            col++;
        }
    }
    return col == 1;
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
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    int l = 0, r = 1e9;
    while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (can(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << (can(l) ? l : r);

    return 0;
}
