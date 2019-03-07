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
#define NAME "sort"
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

ll INF = 1e18;

ll query(ll x) {
	cout << "? " << x + 1 << endl;
	cin >> x;
	return x - 1;
}

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

	ll x, m, y;
	cin >> x >> m;
	x--;
	y = query(0);
	if (x == y) {
		cout << "! 1" << endl;
		return 0;
	}
	ll l, r = x - y;
	if (r < 0) {
		r += INF;
	}
	r = min(r, INF - m - 1);
	l = max(1ll, r - m);
	while (l <= r) {
		ll mid = (l + r) / 2;
		ll a = query(mid);
		if (a == x) {
			cout << "! " << mid + 1 << endl;
			return 0;
		}
		if (l == r && a != x) {
			cout << "! -1" << endl;
			return 0;
		}
		bool flag = a < x;
		if (x > y) {
			flag &= a > y;
		} else {
			flag |= a > y;
		}
		if (flag) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	cout << "! -1" << endl;

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
