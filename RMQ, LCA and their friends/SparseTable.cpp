#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	// freopen("input.txt", "r", stdin);
	const ll mod = 16714589;
	ll n, m, a;
	cin >> n >> m >> a;
	vector<ll> arr(n);
	arr[0] = a;
	for (ll i = 1; i < n; ++i) {
		arr[i] = (23 * arr[i - 1] + 21563) % mod;
	}
	vector<ll> logs(n + 1);
	logs[0] = logs[1] = 0;
	for (ll i = 2; i <= n; ++i) {
		logs[i] = logs[i / 2] + 1;
	}
	const ll INF = 2e18;
	vector<vector<ll>> sparse_table(n, vector<ll>(logs[n] + 1, INF));
	for (ll i = 0; i < n; ++i) {
		sparse_table[i][0] = arr[i];
	}
	for (ll log = 1; log <= logs[n]; ++log) {
		ll len = (1 << log);
		for (ll l = 0; l + len <= n; ++l) {
			sparse_table[l][log] = min(sparse_table[l][log - 1], sparse_table[l + len / 2][log - 1]);
		}
	}
	ll v, u, ans;
	cin >> u >> v;
	for (ll i = 1; i <= m; ++i) {
		ll l = u, r = v;
		if (l > r) {
			swap(l, r);
		}
		l--;
		r--;
		ll len = r - l + 1;
		ans = min(sparse_table[l][logs[len]], sparse_table[r - (1 << logs[len]) + 1][logs[len]]);
		if (i == m) {
			cout << u << " " << v << " " << ans;
			return 0;
		}
		u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
		v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
	}
	return 0;
}
