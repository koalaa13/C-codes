#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

struct Node {
	Node* left;
	Node* right;
	ll value, add;
};

Node* Empty = new Node({ NULL, NULL, 0, 0 });

Node* build(int lb, int rb) {
	if (lb + 1 == rb) {
		return new Node({ Empty, Empty, 0, 0 });
	}
	int mid = (lb + rb) / 2;
	Node* left_ch = build(lb, mid);
	Node* right_ch = build(mid, rb);
	return new Node({ left_ch, right_ch, 0, 0 });
}

inline void push(Node* v) {
	if (v == Empty) {
		return;
	}
	v->value += v->add;
	v->left->add += v->add;
	v->right->add += v->add;
	v->add = 0;
}

void change(Node* v, int l, int r, ll d, int lb, int rb) {
	push(v);
	if (lb >= r || rb <= l) {
		return;
	}
	if (l <= lb && rb <= r) {
		v->add += d;
		return;
	}
	int mid = (lb + rb) / 2;
	change(v->left, l, r, d, lb, mid);
	change(v->right, l, r, d, mid, rb);
}

ll get(Node* v, int pos, int lb, int rb) {
	push(v);
	if (lb + 1 == rb) {
		return v->value;
	}
	int mid = (lb + rb) / 2;
	if (pos < mid) {
		return get(v->left, pos, lb, mid);
	} else {
		return get(v->right, pos, mid, rb);
	}
}

const int N = 3e5 + 11;
const int LOG = 20;
vector<vector<int>> g(N), up(N, vector<int>(LOG));
int timer = 0;
vector<int> path_id(N), path_head(N, -1), subtree(N);
vector<int>tin(N), tout(N), path_size(N), id_in_path(N);
vector<Node*> trees(N);
void dfs(int v, int par = 0) {
	tin[v] = timer++;
	up[v][0] = par;
	for (int i = 1; i < LOG; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (int to : g[v]) {
		if (to != par) {
			dfs(to, v);
		}
	}
	subtree[v] = 1;
	for (int to : g[v]) {
		if (to != par) {
			subtree[v] += subtree[to];
		}
	}
	tout[v] = timer++;
}
int cnt_pathes = 0;
void decomp(int v, int cur_path = 0, int cur_id_in_path = 0, int par = -1) {
	path_id[v] = cur_path;
	id_in_path[v] = cur_id_in_path;
	path_size[cur_path]++;
	if (path_head[cur_path] == -1) {
		path_head[cur_path] = v;
	}
	if (g[v].empty()) {
		return;
	}
	int max_sub = 0, to = -1;
	for (int ch : g[v]) {
		if (ch != par) {
			if (max_sub < subtree[ch]) {
				max_sub = subtree[ch];
				to = ch;
			}
		}
	}
	for (int ch : g[v]) {
		if (ch == par) {
			continue;
		}
		if (ch == to) {
			decomp(ch, cur_path, cur_id_in_path + 1, v);
		} else {
			decomp(ch, ++cnt_pathes, 0, v);
		}
	}
}

inline bool is_par(int v, int u) {
	return tin[v] <= tin[u] && tout[u] <= tout[v];
}

inline int get_lca(int v, int u) {
	if (is_par(v, u)) {
		return v;
	}
	if (is_par(u, v)) {
		return u;
	}
	for (int i = LOG - 1; i >= 0; --i) {
		if (!is_par(up[v][i], u)) {
			v = up[v][i];
		}
	}
	return up[v][0];
}

inline void build_trees() {
	for (int i = 0; i <= cnt_pathes; ++i) {
		trees[i] = build(0, path_size[i]);
	}
}

inline void add_q(int v, int u, ll d) {
	int lca = get_lca(v, u);
	while (path_id[v] != path_id[lca]) {
		change(trees[path_id[v]], 0, id_in_path[v] + 1, d, 0, path_size[path_id[v]]);
		v = up[path_head[path_id[v]]][0];
	}
	while (path_id[u] != path_id[lca]) {
		change(trees[path_id[u]], 0, id_in_path[u] + 1, d, 0, path_size[path_id[u]]);
		u = up[path_head[path_id[u]]][0];
	}
	if (is_par(v, u)) {
		change(trees[path_id[u]], id_in_path[lca], id_in_path[u] + 1, d, 0, path_size[path_id[u]]);
	} else {
		change(trees[path_id[v]], id_in_path[lca], id_in_path[v] + 1, d, 0, path_size[path_id[v]]);
	}
}

inline ll get_q(int v) {
	return get(trees[path_id[v]], id_in_path[v], 0, path_size[path_id[v]]);
}

int main() {
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	dfs(0);
	decomp(0);
	build_trees();
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		char t;
		cin >> t;
		if (t == '+') {
			ll d;
			int v, u;
			cin >> v >> u >> d;
			add_q(v - 1, u - 1, d);
		} else {
			int v;
			cin >> v;
			// printf("%I64d\n", get_q(v - 1));
			cout << get_q(v - 1) << "\n";
		}
	}
	return 0;
}
