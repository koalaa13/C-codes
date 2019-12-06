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

template<class T>
struct dsu {
    int *par, *sz;
    T *data;

    explicit dsu(int n) : par(new int[n]), sz(new int[n]), data(new T[n]) {
        for (int i = 0; i < n; ++i) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    T &operator[](int v) {
        return data[get(v)];
    }

    int get(int v) {
        return par[v] == v ? v : (par[v] = get(par[v]));
    }

    void join(int v, int u, T const &cont) {
        v = get(v);
        u = get(u);
        if (sz[v] > sz[u]) {
            swap(v, u);
        }
        par[v] = u;
        sz[u] += sz[v];
        data[u] = cont;
    }
};

struct treap {
    int from, to;
    ll value, add, mn;
    int pr, to_get_min;  // -1 = go to the left; 0 = min was found; 1 = go to the right

    treap *left, *right;

    explicit treap(int from, int to, ll value) : from(from), to(to), value(value) {
        pr = rand();
        mn = value;
        to_get_min = 0;
        add = 0;
        left = nullptr;
        right = nullptr;
    }

    treap &operator+=(ll d) {
        add += d;
        return *this;
    }

    void push() {
        if (add != 0) {
            if (left != nullptr) {
                left->add += add;
            }
            if (right != nullptr) {
                right->add += add;
            }
            value += add;
            mn += add;
            add = 0;
        }
    }

    void update() {
        mn = value;
        to_get_min = 0;
        if (left != nullptr && left->mn + left->add < mn) {
            mn = left->mn + left->add;
            to_get_min = -1;
        }
        if (right != nullptr && right->mn + right->add < mn) {
            mn = right->mn + right->add;
            to_get_min = 1;
        }
    }
};

treap *merge(treap *l, treap *r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->pr > r->pr) {
        l->push();
        l->right = merge(l->right, r);
        l->update();
        return l;
    } else {
        r->push();
        r->left = merge(l, r->left);
        r->update();
        return r;
    }
}

treap *get_min(treap *t, int &from, int &to, ll &mn) {
    t->push();
    if (t->to_get_min == 0) {
        from = t->from;
        to = t->to;
        mn = t->mn;
        return merge(t->left, t->right);
    } else {
        if (t->to_get_min == -1) {
            t->left = get_min(t->left, from, to, mn);
            mn += t->add;
            t->update();
            return t;
        } else {
            t->right = get_min(t->right, from, to, mn);
            mn += t->add;
            t->update();
            return t;
        }
    }
}

treap *add(treap *t, ll d) {
    return t != nullptr ? (&((*t) += d)) : nullptr;
}

int main() {
#if 0
    freopen("input.txt", "r", stdin);
#else
    //    freopen(FILE".in", "r", stdin);
    //    freopen(FILE".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);

    const int N = 3e5 + 333;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<treap *> edges(n);
    for (int i = 0; i < n; ++i) {
        edges[i] = nullptr;
    }
    for (int i = 0; i < m; ++i) {
        int v, u;
        ll w;
        cin >> v >> u >> w;
        v--;
        u--;
        g[v].push_back(u);
        edges[u] = merge(edges[u], new treap(u, v, w));
    }
    dsu<pair<int, treap *>> d(n);
    for (int i = 0; i < n; ++i) {
        d[i] = {i, edges[i]};
    }
    // check have we got an answer
    queue<int> q;
    bitset<N> used;
    q.push(0);
    used[0] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (!used[to]) {
                used[to] = true;
                q.push(to);
            }
        }
    }
    if ((int) used.count() < n) {
        cout << "NO";
        return 0;
    }
    //
    int cur_comp = n;
    ll ans = 0;
    vector<int> go(2 * n), par(2 * n, -1);
    used.reset();
    for (int i = 0; i < n; ++i) {
        if (d[i].first == 0) {
            continue;
        }
        int u = i;
        used[u] = true;
        for (;;) {
            int from, to;
            ll mn;
            d[u].second = get_min(d[u].second, from, to, mn);
            if (d[to] == d[u]) {
                continue;
            }
            add(d[u].second, -mn);
            ans += mn;
            go[d[u].first] = to;
            if (d[to].first == 0) {
                break;
            }
            if (!used[to]) {
                used[to] = true;
                u = to;
                continue;
            }
            int v = to;  // merge cycle
            par[d[u].first] = cur_comp;
            d[u].first = cur_comp;
            treap *t = d[u].second;
            while (d[v].first != cur_comp) {
                int next = go[d[v].first];
                par[d[v].first] = cur_comp;
                t = merge(t, d[v].second);
                d.join(u, v, {cur_comp, t});
                v = next;
            }
            cur_comp++;
        }
        u = i;
        while (d[u].first != 0) {
            int next = go[d[u].first];
            d.join(u, 0, {0, nullptr});
            u = next;
        }
    }
    cout << "YES\n" << ans;

    return 0;
}
