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

void gen(vector<vector<bool>> &res, bool s) {
    res[0][0] = s;
    int n = (int) res.size();
    int m = (int) res[0].size();
    for (int i = 1; i < m; ++i) {
        res[0][i] = !res[0][i - 1];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j) {
                res[i][j] = !res[i][j - 1];
            } else {
                res[i][j] = !res[i - 1][j];
            }
        }
    }
}

struct diag {
    int x, y, type;
    char col;

    diag() = default;
};

bool dfs(int v, vector<bool> &used, vector<vector<int>> const &connect, vector<int> &match) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int to : connect[v]) {
        if (match[to] == -1 || dfs(match[to], used, connect, match)) {
            match[to] = v;
            return true;
        }
    }
    return false;
}

vector<int> find_matching(int n, int m, vector<vector<int>> const &connect) {
    vector<int> match(m, -1);
    for (int i = 0; i < n; ++i) {
        vector<bool> used(n);
        dfs(i, used, connect, match);
    }
    return match;
}

void col(int v, vector<bool> &used, vector<vector<int>> const &g) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            col(to, used, g);
        }
    }
}

vector<int> find_vertex_cov(int n, int m, vector<vector<int>> const &connect) {
    vector<int> match = find_matching(n, m, connect);
    vector<vector<int>> g(n + m);
    vector<bool> in(n);
    for (int i = 0; i < n; ++i) {
        for (int j : connect[i]) {
            if (i == match[j]) {
                g[j + n].push_back(i);
                in[i] = true;
            } else {
                g[i].push_back(j + n);
            }
        }
    }
    vector<bool> used(n + m);
    for (int i = 0; i < n; ++i) {
        if (!in[i]) {
            col(i, used, g);
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            ans.push_back(i);
        }
    }
    for (int i = n; i < n + m; ++i) {
        if (used[i]) {
            ans.push_back(i);
        }
    }
    return ans;
}

diag get_diag(int v, vector<vector<bool>> const &need, vector<vector<int>> const &xs,
              vector<vector<int>> const &ys) {
    diag res{};
    int n = (int) need.size();
    int m = (int) need[0].size();
    int cnt_diag = n + m - 1;
    if (v < cnt_diag) {
        res.type = 1;
    } else {
        res.type = 2;
        v -= cnt_diag;
    }
    res.x = xs[res.type - 1][v];
    res.y = ys[res.type - 1][v];
    res.type = res.type == 2 ? 1 : 2;
    if (need[res.x - 1][res.y - 1]) {
        res.col = 'W';
    } else {
        res.col = 'B';
    }
    return res;
}

vector<diag> solve(vector<vector<bool>> const &have, vector<vector<bool>> const &need) {
    int n = (int) have.size();
    int m = (int) have[0].size();
    vector<diag> ans;
    int cnt_diag = n + m - 1;
    //  gen
    vector<vector<int>> xs(2, vector<int>(cnt_diag));
    vector<vector<int>> ys(2, vector<int>(cnt_diag));
    for (int i = 0, xx = 1, yy = 1, yy1 = 1; i < cnt_diag; ++i) {
        ys[1][i] = yy1;
        if (i >= m) {
            xx++;
        }
        if (i >= n) {
            yy++;
        }
        if (i + 1 < m) {
            yy1++;
        }
        ys[0][i] = yy;
        xs[0][i] = xs[1][i] = xx;
    }
    reverse(ys[0].begin(), ys[0].end());
    //
    vector<vector<int>> connect(cnt_diag);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (have[i][j] != need[i][j]) {
                int v1 = 0, v2 = 0;
                for (;; ++v1) {
                    if (xs[0][v1] - ys[0][v1] == i - j) {
                        break;
                    }
                }
                for (;; ++v2) {
                    if (xs[1][v2] + ys[1][v2] - 2 == i + j) {
                        break;
                    }
                }
                connect[v1].push_back(v2);
            }
        }
    }
    vector<int> vertex_cov = find_vertex_cov(cnt_diag, cnt_diag, connect);
    ans.reserve(vertex_cov.size());
    for (int v : vertex_cov) {
        ans.push_back(get_diag(v, need, xs, ys));
    }

    return ans;
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

    int n, m;
    cin >> n >> m;
    vector<vector<bool>> b(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            b[i][j] = c == 'W';
        }
    }
    vector<vector<bool>> r1(n, vector<bool>(m)), r2(n, vector<bool>(m));
    gen(r1, false);
    gen(r2, true);
    vector<diag> ans2 = solve(b, r2);
    vector<diag> ans1 = solve(b, r1);
    if (ans1.size() > ans2.size()) {
        ans1.swap(ans2);
    }
    cout << ans1.size() << '\n';
    for (diag d : ans1) {
        cout << d.type << ' ' << d.x << ' ' << d.y << ' ' << d.col << '\n';
    }

    return 0;
}
