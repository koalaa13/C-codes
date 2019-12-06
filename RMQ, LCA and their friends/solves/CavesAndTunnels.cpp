#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Node {
	Node* left;
	Node* right;
	ll mx;
};

const ll INF = 2e18;
Node* Empty = new Node({ NULL, NULL, -INF });

Node* build(int lb, int rb) {
	if (lb + 1 == rb) {
		return new Node({ Empty, Empty, 0 });
	}
	int mid = (lb + rb) / 2;
	Node* left_ch = build(lb, mid);
	Node* right_ch = build(mid, rb);
	return new Node({ left_ch, right_ch, max(left_ch->mx, right_ch->mx) });
}

void add(Node* v, int pos, ll val, int lb, int rb) {
	if (lb + 1 == rb) {
		v->mx += val;
		return;
	}
	int mid = (lb + rb) / 2;
	if (pos < mid) {
		add(v->left, pos, val, lb, mid);
	} else {
		add(v->right, pos, val, mid, rb);
	}
	v->mx = max(v->left->mx, v->right->mx);
}

ll get_max(Node* v, int l, int r, int lb, int rb) {
	if (lb >= r || rb <= l) {
		return -INF;
	}
	if (l <= lb && rb <= r) {
		return v->mx;
	}
	int mid = (lb + rb) / 2;
	return max(get_max(v->left, l, r, lb, mid), get_max(v->right, l, r, mid, rb));
}

const int N = 111111;
const int LOG = 20;
int timer = 0;
vector<vector<int>> g(N), up(N, vector<int>(LOG));
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

bool is_par(int v, int u) {
	return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int get_lca(int v, int u) {
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

void build_trees() {
	for (int i = 0; i <= cnt_pathes; ++i) {
		trees[i] = build(0, path_size[i]);
	}
}

ll v_query(int v, int u) {
	ll ans = -INF;
	while (path_id[v] != path_id[u]) {
		ans = max(ans, get_max(trees[path_id[v]], 0, id_in_path[v] + 1, 0, path_size[path_id[v]]));
		v = up[path_head[path_id[v]]][0];
	}
	ll res = get_max(trees[path_id[v]], id_in_path[u], id_in_path[v] + 1, 0, path_size[path_id[v]]);
	return max(ans, res);
}

ll query(int v, int u) {
	int lca = get_lca(v, u);
	return max(v_query(v, lca), v_query(u, lca));
}

void query_add(int v, int d) {
	add(trees[path_id[v]], id_in_path[v], d, 0, path_size[path_id[v]]);
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
		char type;
		int a, b;
		cin >> type >> a >> b;
		if (type == 'I') {
			query_add(a - 1, (ll)b);
		} else {
			// printf("%I64d\n", query(a - 1, b - 1));
			cout << query(a - 1, b - 1) << "\n";
		}
	}
	return 0;
}
