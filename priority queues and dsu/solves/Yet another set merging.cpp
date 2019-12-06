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
#define NAME "restructure"
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

const int N = 6e5 + 228;
int par[N], par1[N];

int get(int v) {
	if (par[v] != v) {
		par[v] = get(par[v]);
	}
	return par[v];
}

void join(int v, int u) {
	v = get(v);
	u = get(u);
	if (v == u) {
		return;
	}
	if (v > u) {
		par[u] = v;
	} else {
		par[v] = u;
	}
}

int get1(int v) {
	if (par1[v] != v) {
		par1[v] = get1(par1[v]);
	}
	return par1[v];
}

void join1(int v, int u) {
	v = get1(v);
	u = get1(u);
	if (v == u) {
		return;
	}
	if (v > u) {
		par1[u] = v;
	} else {
		par1[v] = u;
	}
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

	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		par[i] = par1[i] = i;
	}
	for (int i = 0; i < q; ++i) {
		int t, x, y;
		cin >> t >> x >> y;
		x--;
		y--;
		if (t == 1) {
			join(x, y);
		}
		if (t == 2) {
			while ((x = get1(x)) < y) {
				join(x, x + 1);
				join1(x, x + 1);
			}
		}
		if (t == 3) {
			if (get(x) == get(y)) {
				cout << "YES\n";
			} else {
				cout << "NO\n";
			}
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
