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

#define mp make_pair
#define NAME "salesman"
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

const int INF = 2e9;

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

	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < m; ++i) {
		int v, u, c;
		cin >> v >> u >> c;
		v--;
		u--;
		g[v].push_back({ u, c });
		g[u].push_back({ v, c });
	}
	int nn = (1 << n);
	vector<vector<int>> dp(nn, vector<int>(n, INF));
	for (int i = 0; i < n; ++i) {
		dp[0][i] = 0;
		dp[1 << i][i] = 0;
	}
	for (int mask = 0; mask < nn; ++mask) {
		for (int i = 0; i < n; ++i) {
			if ((mask & (1 << i)) == 0) {
				for (auto j : g[i]) {
					if (mask & (1 << j.first)) {
						dp[mask | (1 << i)][i] = min(dp[mask | (1 << i)][i], dp[mask][j.first] + j.second);
					}
				}
			}
		}
	}
	int ans = INF;
	for (int i = 0; i < n; ++i) {
		ans = min(ans, dp[nn - 1][i]);
	}
	if (ans == INF) {
		cout << -1;
	} else {
		cout << ans;
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
