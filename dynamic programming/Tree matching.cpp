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
#define NAME "matching"
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

const ll INF = 2e18;
int n;
const int N = 1e5 + 322;
vector<int> type(N);
vector<vector<pair<int, ll>>> g(N);
vector<vector<ll>> dp(N, vector<ll>(2));

void dfs(int v, int par = -1) {
	for (auto to : g[v]) {
		if (to.first != par) {
			dfs(to.first, v);
		}
	}
	dp[v][0] = dp[v][1] = 0;
	ll sum = 0;
	for (auto to : g[v]) {
		if (to.first == par) {
			continue;
		}
		if (dp[to.first][0] > dp[to.first][1]) {
			sum += dp[to.first][0];
			type[to.first] = 0;
		} else {
			sum += dp[to.first][1];
			type[to.first] = 1;
		}
	}
	ll res_dp1 = 0;
	for (auto to : g[v]) {
		if (to.first == par) {
			continue;
		}
		res_dp1 = max(res_dp1, dp[to.first][0] + to.second + sum - dp[to.first][type[to.first]]);
	}
	dp[v][0] = sum;
	dp[v][1] = res_dp1;
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

	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int v, u;
		ll w;
		cin >> v >> u >> w;
		v--;
		u--;
		g[v].push_back({ u, w });
		g[u].push_back({ v, w });
	}
	dfs(0);
	cout << max(dp[0][0], dp[0][1]);

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
