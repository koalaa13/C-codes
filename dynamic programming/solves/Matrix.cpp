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
#define NAME "matrix"
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

const int N = 444;
const ll INF = 2e18;
vector<vector<int>> par(N, vector<int>(N));
vector<vector<ll>> dp(N, vector<ll>(N));
vector<vector<pair<ll, ll>>> ma(N, vector<pair<ll, ll>>(N));

string gen(int l, int r) {
	if (r - l == 1) {
		return "(AA)";
	}
	if (l == r) {
		return "A";
	}
	string left = gen(l, par[l][r]), right = gen(par[l][r] + 1, r);
	string res = "(";
	for (char c : left) {
		res += c;
	}
	for (char c : right) {
		res += c;
	}
	res += ')';
	return res;
}

int main() {
#if SOLVe
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

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		ll a, b;
		cin >> a >> b;
		ma[i][i] = { a, b };
		dp[i][i] = 0;
		par[i][i] = -1;
	}
	for (int len = 2; len <= n; ++len) {
		for (int l = 0; l + len - 1 < n; ++l) {
			int r = l + len - 1;
			ll mn = INF;
			int ind_mn = -1;
			for (int m = l; m < r; ++m) {
				ll val = dp[l][m] + dp[m + 1][r] + ma[l][m].F * ma[l][m].S * ma[m + 1][r].S;
				if (mn > val) {
					mn = val;
					ind_mn = m;
				}
			}
			ma[l][r] = { ma[l][ind_mn].first, ma[ind_mn + 1][r].second };
			dp[l][r] = mn;
			par[l][r] = ind_mn;
		}
	}
	cout << gen(0, n - 1);

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
