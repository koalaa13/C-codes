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

#define FILE "cnf"

typedef long long ll;

using namespace std;

const int N = 1111;
vector<unordered_multiset<int>> g(N);
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

    int s = 0, n, cnt_odd = 0, edges = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int deg;
        cin >> deg;
        edges += deg;
        if (deg % 2 == 1) {
            cnt_odd++;
            s = i;
        }
        for (int j = 0; j < deg; ++j) {
            int u;
            cin >> u;
            g[i].insert(u - 1);
        }
    }
    dfs(s);
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() > 0) {
            flag &= used[i];
        }
    }
    if (cnt_odd > 2 || !flag) {
        cout << -1;
        return 0;
    }
    stack<int> st;
    st.push(s);
    vector<int> ans;
    while (!st.empty()) {
        int v = st.top();
        while (!g[v].empty()) {
            int u = *g[v].begin();
            st.push(u);
            g[v].erase(g[v].find(u));
            g[u].erase(g[u].find(v));
            break;
        }
        if (v == st.top()) {
            st.pop();
            ans.push_back(v);
        }
    }
    cout << edges / 2 << '\n';
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
        cout << *it + 1 << ' ';
    }


    return 0;
}
