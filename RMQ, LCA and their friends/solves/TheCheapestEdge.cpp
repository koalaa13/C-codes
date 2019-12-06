#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 11;
const int LOG = 19;
vector<vector<int>> up(N, vector<int> (LOG)), mins(N, vector<int> (LOG));
vector<vector<pair<int, int>>> g(N);
vector<int> tin(N), tout(N);
int timer = 0;

void dfs(int v, int par, int w) {
	up[v][0] = par;
	mins[v][0] = w;
	tin[v] = timer++;
	for (int i = 1; i < LOG; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
		mins[v][i] = min(mins[v][i - 1], mins[up[v][i - 1]][i - 1]);
	}
	for (pair<int, int> to : g[v]) {
		dfs(to.first, v, to.second);
	}
	tout[v] = timer++;
}

bool is_par(int v, int u) {
	return tin[v] <= tin[u] && tout[u] <= tout[v];
}

const int INF = 2e9;
int get_min(int v, int u) {
	int ans = INF;
	if (!is_par(v, u)) {
		int v1 = v;
		for (int i = LOG - 1; i >= 0; --i) {
			if (!is_par(up[v1][i], u)) {
				ans = min(ans, mins[v1][i]);
				v1 = up[v1][i];
			}
		}
		ans = min(ans, mins[v1][0]);
	}
	if (!is_par(u, v)) {
		int u1 = u;
		for (int i = LOG - 1; i >= 0; --i) {
			if (!is_par(up[u1][i], v)) {
				ans = min(ans, mins[u1][i]);
				u1 = up[u1][i];
			}
		}
		ans = min(ans, mins[u1][0]);
	}
	return ans;
}

int main() {
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		g[x - 1].push_back({ i, y });
	}
	dfs(0, 0, INF);
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		cout << get_min(x - 1, y - 1) << "\n";
	}

	return 0;
}
