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
#define NAME "perm"
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

ll gcd(ll a, ll b) {
	while (a * b > 0) {
		if (a > b) {
			a %= b;
		} else {
			b %= a;
		}
	}
	return a + b;
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

	ll n, m, k;
	cin >> n >> m >> k;
	m--;
	vector<ll> arr(n);
	for (ll i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());
	vector<vector<ll>> dp(1 << n, vector<ll>(n, 0));
	vector<vector<ll>> g(n);
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < i; ++j) {
			if (gcd(arr[i], arr[j]) >= k) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}
	for (ll i = 0; i < n; ++i) {
		dp[0][i] = 1;
		dp[1 << i][i] = 1;
	}
	for (ll mask = 0; mask < (1 << n); ++mask) {
		for (ll i = 0; i < n; ++i) {
			if ((mask & (1 << i)) == 0) {
				for (ll j : g[i]) {
					if (mask & (1 << j)) {
						dp[mask | (1 << i)][i] += dp[mask][j];
					}
				}
			}
		}
	}
	ll all_count = 0, mask = (1 << n) - 1;
	for (ll i = 0; i < n; ++i) {
		all_count += dp[mask][i];
	}
	if (all_count <= m) {
		cout << -1;
		return 0;
	}
	vector<ll> ans;
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < n; ++j) {
			if (mask & (1 << j)) {
				bool can = 1;
				if (!ans.empty()) {
					bool has = 0;
					for (ll v : g[ans.back()]) {
						has |= v == j;
					}
					can &= has;
				}
				if (!can) {
					continue;
				}
				ll cnt = dp[mask][j];
				if (cnt > m) {
					ans.push_back(j);
					mask ^= (1 << j);
					break;
				} else {
					m -= cnt;
				}
			}
		}
	}
	for (ll i : ans) {
		cout << arr[i] << " ";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
