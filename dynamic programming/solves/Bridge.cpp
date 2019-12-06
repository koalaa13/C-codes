#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>
#include <ctime>
#include <cassert>
#include <complex>
#include <stdlib.h>
#include <limits>
// #pragma comment(linker, "/STACK:256000000")
using namespace std;

#define F first
#define S second
#define mp make_pair
#define NAME "bridge"
/* #define FAST_ALLOCATOR_MEMORY 2e8
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void* operator new(size_t n) {
char* res = allocator_memory + allocator_pos;
allocator_pos += n;
assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
return (void*)res;
}
inline void operator delete(void*)noexcept {}
// inline void * operator new [] ( size_t ) { assert(0); }
// inline void operator delete [] ( void * ) { assert(0); }
#endif */

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int N = 333;

int div_up(int a, int b) {
	int res = a / b;
	if (a % b > 0) {
		res++;
	}
	return res;
}

int x, a, y, b, len;
const int INF = 2e9;

int dp[N][N];
int calc_dp(int m) {
	for (int i = 0; i <= x; ++i) {
		int in_row = div_up(m, a);
		dp[i][0] = i / in_row;
	}
	for (int i = 0; i <= y; ++i) {
		int in_row = div_up(m, b);
		dp[0][i] = i / in_row;
	}
	for (int i = 1; i <= x; ++i) {
		for (int j = 1; j <= y; ++j) {
			int mx = -INF;
			for (int k = 0; k <= i; ++k) {
				int cnt_need = 0;
				if (m > a * k) {
					cnt_need = div_up(m - a * k, b);
				}
				if (cnt_need > j) {
					continue;
				}
				mx = max(mx, dp[i - k][j - cnt_need]);
			}
			if (mx == -INF) {
				dp[i][j] = 0;
			} else {
				dp[i][j] = mx + 1;
			}
		}
	}
	int mx = -INF;
	for (int i = 0; i <= x; ++i) {
		for (int j = 0; j <= y; ++j) {
			mx = max(mx, dp[i][j]);
		}
	}
	return mx;
}

int main() {
#if SOLVE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	freopen(NAME".in", "r", stdin);
	freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// srand(time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);

	int l = 1, r = 111111;
	cin >> x >> a >> y >> b >> len;
	calc_dp(250);
	while (r - l > 1) {
		int m = (l + r) / 2;
		int res = calc_dp(m);
		if (res >= len) {
			l = m;
		} else {
			r = m;
		}
	}
	if (calc_dp(r) >= len) {
		cout << r;
	} else {
		cout << l;
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
