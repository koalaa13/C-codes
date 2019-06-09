#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int sq = 500;
const int N = 1e6 + 7;

struct q {
	int l, r, ind;
};

bool cmp(q const &a, q const &b) {
	int block_a = a.l / sq, block_b = b.l / sq;
	if (block_a != block_b) {
		return block_a < block_b;
	}
	if ((block_a & 1) == 0) {
		return a.r < b.r;
	}
	return a.r > b.r;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> numbers(N), arr(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &arr[i]);
	}
	vector<q> qs(m);
	for (int i = 0; i < m; ++i) {
		cin >> qs[i].l >> qs[i].r;
		--qs[i].l;
		--qs[i].r;
		qs[i].ind = i;
	}
	sort(qs.begin(), qs.end(), cmp);
	vector<ll> ans(m);
	ll answer = 0;
	for (int i = 0; i < m; ++i) {
		if (i > 0) {
			if (qs[i].l < qs[i - 1].l) {
				for (int j = qs[i].l; j < qs[i - 1].l; ++j) {
					answer += arr[j] * (2 * numbers[arr[j]] + 1);
					++numbers[arr[j]];
				}
			}
			if (qs[i].l > qs[i - 1].l) {
				for (int j = qs[i - 1].l; j < qs[i].l; ++j) {
					answer += arr[j] * (-2 * numbers[arr[j]] + 1);
					--numbers[arr[j]];
				}
			}
			if (qs[i].r < qs[i - 1].r) {
				for (int j = qs[i].r + 1; j <= qs[i - 1].r; ++j) {
					answer += arr[j] * (-2 * numbers[arr[j]] + 1);
					--numbers[arr[j]];
				}
			}
			if (qs[i].r > qs[i - 1].r) {
				for (int j = qs[i - 1].r + 1; j <= qs[i].r; ++j) {
					answer += arr[j] * (2 * numbers[arr[j]] + 1);
					++numbers[arr[j]];
				}
			}
			ans[qs[i].ind] = answer;
		} else {
			for (int j = qs[i].l; j <= qs[i].r; ++j) {
				answer += arr[j] * (2 * numbers[arr[j]] + 1);
				++numbers[arr[j]];
			}
			ans[qs[i].ind] = answer;
		}
	}
	for (int i = 0; i < m; ++i) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
