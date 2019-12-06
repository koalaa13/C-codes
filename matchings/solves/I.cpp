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

int d, k, d_n = 1;

int to(vector<int> const &number) {
    int res = 0, p = 1;
    for (size_t i = 0; i < number.size(); ++i, p *= d) {
        res += p * number[i];
    }
    return res;
}

string from(int number) {
    string res;
    for (int i = 0; i < k; ++i) {
        res += (char) ('0' + (number % d));
        number /= d;
    }
    reverse(res.begin(), res.end());
    return res;
}

void rec(vector<int> &data, vector<int> &res) {
    if ((int) data.size() == k) {
        res.push_back(to(data));
        return;
    }
    for (int i = 0; i < d; ++i) {
        data.push_back(i);
        rec(data, res);
        data.pop_back();
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
    cin.tie(nullptr);

    cin >> d >> k;
    if (k == 1) {
        for (int i = 0; i < d; ++i) {
            cout << i;
        }
        return 0;
    }
    for (int i = 0; i < k - 1; ++i) {
        d_n *= d;
    }
    vector<vector<int>> g(d_n);
    vector<int> ptr(d_n);
    vector<int> es;
    vector<int> tmp;
    rec(tmp, es);
    for (int e : es) {
        int v = e / d;
        int u = e % d_n;
        g[v].push_back(u);
    }
    vector<int> path;
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int v = st.top();
        if (ptr[v] < (int) g[v].size()) {
            int u = g[v][ptr[v]++];
            st.push(u);
            continue;
        }
        if (v == st.top()) {
            st.pop();
            path.push_back(v);
        }
    }
    reverse(path.begin(), path.end());
    vector<int> ans;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int v = path[i];
        int u = path[i + 1];
        int edge = (v * d) + (u % d);
        ans.push_back(edge);
    }
    cout << from(ans[0]);
    for (size_t i = 1; i < ans.size(); ++i) {
        cout << ans[i] % d;
    }


    return 0;
}
