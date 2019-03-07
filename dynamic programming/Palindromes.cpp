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
#define NAME "sequences"
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

const ll MOD = 1e9;

int main() {
#if _DEBUG
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	// freopen(NAME".in", "r", stdin);
	// freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// srand(time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);

	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	vector<vector<ll>> dp(n + 11, vector<ll>(n + 11));
	for (int i = 0; i < n; ++i) {
		dp[i][i] = 1;
	}
	for (int i = 0; i + 1 < n; ++i) {
		dp[i][i + 1] = 2 + (arr[i] == arr[i + 1]);
	}
	for (int len = 3; len <= n; ++len) {
		for (int l = 0; l + len - 1 < n; ++l) {
			int r = l + len - 1;
			dp[l][r] = ((dp[l + 1][r] + dp[l][r - 1]) % MOD - dp[l + 1][r - 1] + MOD) % MOD;
			if (arr[l] == arr[r]) {
				dp[l][r] = (dp[l][r] + dp[l + 1][r - 1] + 1) % MOD;
			}
		}
	}
	cout << dp[0][n - 1];

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
