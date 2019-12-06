#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int u_int;

u_int a, b, cur = 0;
u_int nextRand() {
	cur = cur * a + b;
	return cur >> 8;
}

int main() {
	// freopen("input.txt", "r", stdin);
	const size_t N = (1 << 24) + 11;
	u_int m, q;
	cin >> m >> q >> a >> b;
	vector<u_int> diff(N);
	for (u_int i = 0; i < m; ++i) {
		u_int add = nextRand();
		u_int l = nextRand();
		u_int r = nextRand();
		if (l > r) {
			swap(l, r);
		}
		diff[l] += add;
		diff[r + 1] -= add;
		// cout << l << " " << r << " " << add << "\n";
	}
	// cout << diff[375524];
	vector<u_int> pref(N);
	for (u_int i = 1, cur = 0; i < N; ++i) {
		cur += diff[i - 1];
		pref[i] = pref[i - 1] + cur;
	}
	u_int sum = 0;
	for (u_int i = 0; i < q; ++i) {
		u_int l = nextRand();
		u_int r = nextRand();
		if (l > r) {
			swap(l, r);
		}
		sum += pref[r + 1] - pref[l];
	}
	cout << sum;

	return 0;
}
