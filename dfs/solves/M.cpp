#include <fstream>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#define FILE "tiv"

using namespace std;

const int N = 26;
vector<vector<bool>> g(N, vector<bool>(N));
vector<int> col(N), order;
set<int> not_zeroes;

void no_ans() {
    cout << "No";
    exit(0);
}

void dfs(int v) {
    col[v] = 1;
    for (int i = 0; i < N; ++i) {
        if (g[v][i]) {
            if (col[i] == 1) {
               no_ans();
            }
            if (col[i] == 0) {
                dfs(i);
            }
        }
    }
    order.push_back(v);
    col[v] = 2;
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
        freopen(FILE".in", "r", stdin);
        freopen(FILE".out", "w", stdout);
#endif
    int n;
    string s, was;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        if (s.size() > 1) {
            not_zeroes.insert(s[0] - 'a');
        }
        if (i) {
            if (was.size() > s.size()) {
                no_ans();
            }
            if (was.size() == s.size()) {
                size_t ind = 0;
                while (ind < was.size() && s[ind] == was[ind]) {
                    ++ind;
                }
                if (ind == was.size()) {
                    no_ans();
                } else {
                    g[s[ind] - 'a'][was[ind] - 'a'] = true;
                }
            }
        }
        was = s;
    }
    set<int> have;
    for (int i = 0; i < N; ++i) {
        have.insert(i + 1);
    }
    vector<int> ans(N);
    for (int i = 0; i < N; ++i) {
        if (col[i] == 0) {
            dfs(i);
        }
    }
    bool set_zero = false;
    for (int i = 0; i < N; ++i) {
        int out = 0;
        for (int j = 0; j < N; ++j) {
            out += g[i][j];
        }
        if (out == 0 && not_zeroes.count(i) == 0) {
            ans[i] = 1;
            have.erase(1);
            set_zero = true;
            break;
        }
    }
    if (!set_zero) {
        no_ans();
    }
    for (int v : order) {
        if (ans[v] == 0) {
            ans[v] = *have.begin();
            have.erase(have.begin());
        }
    }
    cout << "Yes\n";
    for (int i = 0; i < N; ++i) {
        cout << ans[i] - 1 << ' ';
    }

    return 0;
}
