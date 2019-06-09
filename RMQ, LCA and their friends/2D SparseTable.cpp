#include <vector>
#include <functional>
#include <cstdio>

using namespace std;

const int N = 130;
const int LOG = 8;
int logs[N];

void prec() {
	logs[0] = logs[1] = 0;
	for (int i = 2; i < N; ++i) {
		logs[i] = logs[i >> 1] + 1;
	}
}

typedef vector<vector<vector<vector<int>>>> st;
typedef long long ll;

inline int my_max(int const &a, int const &b) {
	return a > b ? a : b;
}

inline int my_min(int const &a, int const &b) {
	return a < b ? a : b;
}

const int INF = 2e9;
int st1[N][N][LOG][LOG];
int st2[N][N][LOG][LOG];
int st3[N][N][LOG][LOG];
int st4[N][N][LOG][LOG];
int right_xs[N][N];
int left_xs[N][N];
int up_ys[N][N];
int down_ys[N][N];
inline void build_sparse_tables(int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			st1[i][j][0][0] = left_xs[i][j];
			st2[i][j][0][0] = right_xs[i][j];
			st3[i][j][0][0] = down_ys[i][j];
			st4[i][j][0][0] = up_ys[i][j];
		}
	}
	for (int k = 1; k < LOG; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m - (1 << (k - 1)); ++j) {
				st1[i][j][0][k] = my_max(st1[i][j][0][k - 1], st1[i][j + (1 << (k - 1))][0][k - 1]);
				st2[i][j][0][k] = my_min(st2[i][j][0][k - 1], st2[i][j + (1 << (k - 1))][0][k - 1]);
				st3[i][j][0][k] = my_max(st3[i][j][0][k - 1], st3[i][j + (1 << (k - 1))][0][k - 1]);
				st4[i][j][0][k] = my_min(st4[i][j][0][k - 1], st4[i][j + (1 << (k - 1))][0][k - 1]);
			}
		}
	}
	for (int k1 = 1; k1 < LOG; ++k1) {
		for (int i = 0; i < n - (1 << (k1 - 1)); ++i) {
			for (int k2 = 0; k2 < LOG; ++k2) {
				for (int j = 0; j < m; ++j) {
					st1[i][j][k1][k2] = my_max(st1[i][j][k1 - 1][k2], st1[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
					st2[i][j][k1][k2] = my_min(st2[i][j][k1 - 1][k2], st2[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
					st3[i][j][k1][k2] = my_max(st3[i][j][k1 - 1][k2], st3[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
					st4[i][j][k1][k2] = my_min(st4[i][j][k1 - 1][k2], st4[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
				}
			}
		}
	}
}

inline int query(function<int(int, int)> f, int x1, int y1,
	int x2, int y2, int const table[N][N][LOG][LOG]) {
	int k1 = logs[x2 - x1 + 1];
	int k2 = logs[y2 - y1 + 1];
	int ans1 = table[x1][y1][k1][k2];
	int ans2 = table[x2 - (1 << k1) + 1][y1][k1][k2];
	int ans3 = table[x1][y2 - (1 << k2) + 1][k1][k2];
	int ans4 = table[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2];
	return f(f(ans1, ans2), f(ans3, ans4));
}

inline ll get_s(int x1, int y1, int x2, int y2) {
	if (x1 >= x2 || y1 >= y2) {
		return 0;
	}
	return (ll)(x2 - x1) * (ll)(y2 - y1);
}

template<typename T>
inline T take_mod(T const &n, T const &mod) {
	if (n < mod) {
		return n;
	}
	return n % mod;
}

int main() {
	// freopen("input.txt", "r", stdin);
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	int n, m;
	scanf("%d%d", &n, &m);
	prec();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if (x1 > x2) {
				swap(x1, x2);
			}
			if (y1 > y2) {
				swap(y1, y2);
			}
			left_xs[i][j] = x1;
			right_xs[i][j] = x2;
			down_ys[i][j] = y1;
			up_ys[i][j] = y2;
		}
	}
	build_sparse_tables(n, m);
	const ll mod = 1e9 + 7;
	ll ans = 0;
	int q, arr[4];
	ll a, b, was;
	scanf("%d%I64d%I64d%I64d", &q, &a, &b, &was);
	while (q--) {
		for (int i = 0; i < 4; ++i) {
			arr[i] = (int)(take_mod(was * a + b, mod));
			was = arr[i];
		}
		int l1 = take_mod(arr[0], n), r1 = take_mod(arr[1], m);
		int l2 = take_mod(arr[2], n), r2 = take_mod(arr[3], m);
		if (l1 > l2) {
			swap(l1, l2);
		}
		if (r1 > r2) {
			swap(r1, r2);
		}
		int x1 = query(my_max, l1, r1, l2, r2, st1);
		int x2 = query(my_min, l1, r1, l2, r2, st2);
		int y1 = query(my_max, l1, r1, l2, r2, st3);
		int y2 = query(my_min, l1, r1, l2, r2, st4);
		ll sq = get_s(x1, y1, x2, y2);
		ans = take_mod(ans + sq, mod);
	}
	printf("%I64d", ans);

	return 0;
}
