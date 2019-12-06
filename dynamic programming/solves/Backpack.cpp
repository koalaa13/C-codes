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
#define NAME "knapsack"
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

	int n, W;
	cin >> n >> W;
	vector<int> c(n + 1), w(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
	}
	vector<vector<int>> dp(n + 22, vector<int>(W + 22, -INF)), par(n + 22, vector<int> (W + 22, 0));
	for (int i = 0; i <= W; ++i) {
		dp[0][i] = 0;
	}
	for (int i = 0; i <= n; ++i) {
		dp[i][0] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= W; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j - w[i] >= 0) {
				if (dp[i][j] < dp[i - 1][j - w[i]] + c[i]) {
					dp[i][j] = dp[i - 1][j - w[i]] + c[i];
					par[i][j] = 1;
				}
			}
		}
	}
	int ans = -1, ans_c = -INF;
	for (int i = 0; i <= W; ++i) {
		if (ans_c < dp[n][i]) {
			ans = i;
			ans_c = dp[n][i];
		}
	}
	int ind = n;
	vector<int> obs;
	while (ind > 0) {
		if (par[ind][ans]) {
			obs.push_back(ind);
			ans -= w[ind];
		}
		--ind;
	}
	cout << obs.size() << "\n";
	reverse(obs.begin(), obs.end());
	for (int i : obs) {
		cout << i << " ";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
