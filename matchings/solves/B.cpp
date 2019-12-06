#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>

#define FILE "cnf"

typedef long long ll;

using namespace std;

const int N = 1111;
vector<vector<int>> g(N);
vector<int> match(N, -1);
bitset<N> used;

bool dfs(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int to : g[v]) {
        if (match[to] == -1 || dfs(match[to])) {
            match[to] = v;
            return true;
        }
    }
    return false;
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
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
    }
    for (int i = 0; i < n; ++i) {
        used.reset();
        dfs(i);
    }
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        answer += (match[i] != -1);
    }
    cout << n - answer;

    return 0;
}
