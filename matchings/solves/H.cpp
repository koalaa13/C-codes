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

#define FILE "cnf"

typedef long long ll;

using namespace std;

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
    vector<unordered_multiset<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        g[v].insert(u);
        g[u].insert(v);
    }
    vector<int> odds;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() % 2 == 1) {
            odds.push_back(i);
        }
    }
    vector<unordered_multiset<int>> added(n);
    for (int i = 0; i < (int) odds.size() - 2; ++i) {
        int v = odds[i];
        int u = odds[++i];
        g[v].insert(u);
        g[u].insert(v);
        added[v].insert(u);
        added[u].insert(v);
    }
    stack<int> st;
    st.push(odds.empty() ? 0 : *odds.rbegin());
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
    cout << (odds.empty() ? 1 : odds.size() / 2) << '\n';
    vector<int> cur_path;
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) {
            int v = ans[i];
            int u = ans[i - 1];
            if (added[v].find(u) != added[v].end()) {
                added[v].erase(added[v].find(u));
                added[u].erase(added[u].find(v));
                for (int j : cur_path) {
                    cout << j + 1 << ' ';
                }
                cout << '\n';
                cur_path.clear();
            }
        }
        cur_path.push_back(ans[i]);
    }
    for (int j : cur_path) {
        cout << j + 1 << ' ';
    }

    return 0;
}
