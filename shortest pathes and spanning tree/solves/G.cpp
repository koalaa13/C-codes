#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
#include <cmath>

#define FILE "cnf"

using namespace std;

typedef long long ll;
typedef long double ld;

int len(pair<int, int> const &a, pair<int, int> const &b) {
    int x = abs(a.first - b.first);
    int y = abs(a.second - b.second);
    return x * x + y * y;
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    //    freopen(FILE".in", "r", stdin);
    //    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int, int>> ps(n);
    for (int i = 0; i < n; ++i) {
        cin >> ps[i].first >> ps[i].second;
    }
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = len(ps[i], ps[j]);
        }
    }
    const ll INF = 2e18;
    vector<ll> d(n, INF);
    d[0] = 0;
    vector<bool> used(n);
    ld ans = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || d[v] > d[j])) {
                v = j;
            }
        }
        used[v] = true;
        if (d[v] != INF) {
            ans += sqrt(d[v]);
        }
        for (int j = 0; j < n; ++j) {
            if (g[v][j] < d[j]) {
                d[j] = g[v][j];
            }
        }
    }
    cout.precision(20);
    cout << fixed << ans;

    return 0;
}
