#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int LOG = 19;
const int N = 5e5 + 11;
vector<vector<int>> up(N, vector<int>(LOG)), g(N);
vector<int> tin(N), tout(N);
int timer = 0;
void dfs(int v, int par = 0) {
	up[v][0] = par;
	tin[v] = timer++;
	for (int i = 1; i < LOG; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (int to : g[v]) {
		dfs(to, v);
	}
	tout[v] = timer++;
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int m;
	cin >> m;
	vector<pair<int, int>> qs;
	for (int i = 0; i < m; ++i) {
		string type;
		int a, b;
		cin >> type >> a >> b;
		if (type == "ADD") {
			g[a - 1].push_back(b - 1);
		} else {
			qs.push_back({ a - 1, b - 1 });
		}
	}
	dfs(0);
	for (pair<int, int> q : qs) {
		cout << get_lca(q.first, q.second) + 1 << "\n";
	}
	return 0;
}
