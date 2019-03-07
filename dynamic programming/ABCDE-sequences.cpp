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
typedef vector<vector<ll>> matrix;

const ll MOD = 999999937;

matrix mul(const matrix &a, const matrix &b) {
	int n = (int)a.size(), m = (int)b[0].size();
	matrix res(n, vector<ll> (m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			ll sum = 0;
			for (int k = 0; k < (int)b.size(); ++k) {
				sum = (sum + (a[i][k] * b[k][j]) % MOD) % MOD;
			}
			res[i][j] = sum;
		}
	}
	return res;
}

matrix pow(matrix a, ll p) {
	if (p == 1) {
		return a;
	}
	if (p % 2 == 0) {
		matrix res = pow(a, p / 2);
		return mul(res, res);
	}
	return mul(a, pow(a, p - 1));
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

	for (;;) {
		ll n;
		cin >> n;
		if (n == 1) {
			cout << "5\n";
			continue;
		}
		if (!n) {
			break;
		}
		matrix a(5);
		a[0] = { 1, 1, 1, 1, 1 };
		a[1] = { 1, 1, 1, 1, 1 };
		a[2] = { 1, 1, 1, 1, 1 };
		a[3] = { 1, 1, 0, 1, 0 };
		a[4] = { 1, 1, 0, 1, 0 };
		a = pow(a, n - 1);
		matrix b(5);
		b[0] = { 1 };
		b[1] = { 1 };
		b[2] = { 1 };
		b[3] = { 1 };
		b[4] = { 1 };
		a = mul(a, b);
		ll ans = 0;
		for (int i = 0; i < 5; ++i) {
			ans = (ans + a[i][0]) % MOD;
		}
		cout << ans << "\n";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
