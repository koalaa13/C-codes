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
#define NAME "optimalcode"
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

const ll INF = 2e18 + 11;
const int N = 2222;
vector<vector<ll>> dp(N, vector<ll>(N, INF)), par(N, vector<ll>(N, -1));

void rec(ll l, ll r, string s = "") {
	if (r - l == 0) {
		cout << s << "\n";
		return;
	}
	ll m = par[l][r];
	rec(l, m, s + '0');
	rec(m + 1, r, s + '1');
}

int main() {
#if SOLVE
	freopen("input.txt", "r", stdin);
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

	ll n;
	cin >> n;
	vector<ll> sums(n + 1);
	for (ll i = 1; i <= n; ++i) {
		ll f;
		cin >> f;
		sums[i] = sums[i - 1] + f;
	}
	for (ll i = 0; i < n; ++i) {
		dp[i][i] = 0;
		par[i][i] = i;
	}
	for (ll len = 2; len <= n; ++len) {
		for (ll l = 0; l + len - 1 < n; ++l) {
			ll r = l + len - 1, mn = INF, p = -1;
			for (ll k = par[l][r - 1]; k <= par[l + 1][r]; ++k) {
				if (dp[l][k] + dp[k + 1][r] < mn) {
					mn = dp[l][k] + dp[k + 1][r];
					p = k;
				}
			}
			ll sum = sums[r + 1] - sums[l];
			dp[l][r] = mn + sum;
			par[l][r] = p;
		}
	}
	cout << dp[0][n - 1] << "\n";
	rec(0, n - 1);

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
