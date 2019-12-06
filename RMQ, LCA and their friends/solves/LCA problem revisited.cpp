#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 111;
const int LOG = 20;
const int INF = 2e9;
vector<vector<int>> g(N);
vector<int> vs(N), logs(N), first_entry(N, -1);
vector<vector<pair<int, int>>> st(N, vector<pair<int, int>>(LOG, { INF, -1 }));
int ind = 0;

void dfs(int v, int dep = 0) {
	st[ind][0] = { dep, ind};
	vs[ind++] = v;
	for (int to : g[v]) {
		dfs(to, dep + 1);
		st[ind][0] = { dep, ind };
		vs[ind++] = v;
	}
}

void prec() {
	logs[0] = logs[1] = 0;
	for (int i = 2; i < N; ++i) {
		logs[i] = logs[i >> 1] + 1;
	}
	for (int log = 1; log < LOG; ++log) {
		int len = (1 << log);
		for (int l = 0; l + len <= N; ++l) {
			st[l][log] = min(st[l][log - 1], st[l + len / 2][log - 1]);
		}
	}
	for (int i = 0; i < ind; ++i) {
		if (first_entry[vs[i]] == -1) {
			first_entry[vs[i]] = i;
		}
	}
}

int get_lca(int v, int u) {
	int l = first_entry[v], r = first_entry[u];
	if (l > r) {
		swap(l, r);
	}
	int len = r - l + 1;
	pair<int, int> mn = min(st[l][logs[len]], st[r - (1 << logs[len]) + 1][logs[len]]);
	return vs[mn.second];
}

int main() {
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n - 1; ++i) {
		int par;
		cin >> par;
		g[par].push_back(i + 1);
	}
	dfs(0);
	prec();
	vector<int> as(2 * m + 11);
	long long x, y, z;
	cin >> as[1] >> as[2] >> x >> y >> z;
	for (size_t i = 3; i < as.size(); ++i) {
		as[i] = (int)((x * (long long)as[i - 2] + y * (long long)as[i - 1] + z) % (long long)n);
	}
	long long ans = 0, was;
	for (int i = 1; i <= m; ++i) {
		int lca;
		if (i == 1) {
			lca = get_lca(as[1], as[2]);
		} else {
			lca = get_lca((int)((as[2 * i - 1] + was) % n), as[2 * i]);
		}
		ans += (long long)lca;
		was = lca;
	}
	cout << ans;

	return 0;
}
