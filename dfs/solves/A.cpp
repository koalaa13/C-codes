#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "topsort"
#define _DEBUG 1

using namespace std;

const int N = 111111;
vector<vector<int>> g(N);
vector<int> order, col(N);

void dfs(int v) {
    col[v] = 1;
    for (int to : g[v]) {
        if (col[to] == 1) {
            cout << -1;
            exit(0);
        }
        if (col[to] == 0) {
            dfs(to);
        }
    }
    col[v] = 2;
    order.push_back(v);
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    freopen(FILE".in", "r", stdin);
    freopen(FILE".out", "w", stdout);
#endif
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
    auto print = [](const int &v) { cout << v + 1 << ' '; };
    for_each(order.rbegin(), order.rend(), print);

    return 0;
}
