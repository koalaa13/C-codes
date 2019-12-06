#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5 + 111;
const int LOG = 20;
vector<vector<int>> g, up(N, vector<int>(LOG));
vector<int> tin(N), tout(N), ds(N);
int timer = 0;

void dfs(int v = 0, int par = 0, int dep = 0) {
	tin[v] = timer++;
	up[v][0] = par;
	ds[v] = dep;
	for (int i = 1; i < LOG; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (int to : g[v]) {
		if (to != par) {
			dfs(to, v, dep + 1);
		}
	}
	tout[v] = timer++;
}

bool is_par(int v, int u) {
	return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int get_normal_lca(int v, int u) {
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

int get_d(int v, int u) {
	if (is_par(v, u)) {
		return ds[u] - ds[v];
	}
	if (is_par(u, v)) {
		return ds[v] - ds[u];
	}
	int lca = get_normal_lca(v, u);
	return ds[v] + ds[u] - 2 * ds[lca];
}

int get_lca(int root, int v, int u) {
	if (is_par(root, v) && is_par(root, u)) {
		return get_normal_lca(v, u);
	}
	if (!is_par(root, v) && is_par(root, u)) {
		return root;
	}
	if (is_par(root, v) && !is_par(root, u)) {
		return root;
	}
	int z = root;
	for (int i = LOG - 1; i >= 0; --i) {
		if (!is_par(up[z][i], v) && !is_par(up[z][i], u)) {
			z = up[z][i];
		}
	}
	z = up[z][0];
	int lca_vu = get_normal_lca(v, u);
	if (is_par(lca_vu, z)) {
		return z;
	} else {
		return lca_vu;
	}
}

int main() {
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (true) {
		int cur_root = 0, n, m;
		cin >> n;
		if (n == 0) {
			return 0;
		}
		g.clear();
		g.resize(n);
		for (int i = 0; i < n - 1; ++i) {
			int v, u;
			cin >> v >> u;
			g[v - 1].push_back(u - 1);
			g[u - 1].push_back(v - 1);
		}
		dfs();
		cin >> m;
		for (int i = 0; i < m; ++i) {
			char c;
			cin >> c;
			if (c == '?') {
				int v, u;
				cin >> v >> u;
				cout << get_lca(cur_root, v - 1, u - 1) + 1 << "\n";
				// printf("%d\n", get_lca(cur_root, v - 1, u - 1) + 1);
			} else {
				int v;
				cin >> v;
				cur_root = v - 1;
			}
		}
		// cerr << "\n";
	}

	return 0;
}
