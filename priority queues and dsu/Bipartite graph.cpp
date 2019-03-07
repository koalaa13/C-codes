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
#define NAME "dsu"
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

const int N = 3e5 + 228;
int par[N], sz[N], shift = 0;
bool rev[N], need_rev;

int get(int v) {
	need_rev ^= rev[v];
	if (par[v] != v) {
		return get(par[v]);
	}
	return par[v];
}

bool get_col(int v) {
	need_rev = 0;
	get(v);
	return need_rev;
}

void join(int v, int u) {
	bool flag = get_col(v) == get_col(u);
	v = get(v);
	u = get(u);
	if (v == u) {
		return;
	}
	if (sz[v] > sz[u]) {
		if (flag) {
			rev[u] ^= 1;
		}
		par[u] = v;
		sz[v] += sz[u];
	} else {
		if (flag) {
			rev[v] ^= 1;
		}
		par[v] = u;
		sz[u] += sz[v];
	}
}

int main() {
#if _DEBUG
	freopen("input.txt", "r", stdin);
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

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		par[i] = i;
		sz[i] = 1;
		rev[i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		int type, a, b;
		cin >> type >> a >> b;
		a = (a + shift) % n;
		b = (b + shift) % n;
		if (!type) {
			join(a, b);
		} else {
			bool cola = get_col(a), colb = get_col(b);
			if (cola != colb) {
				cout << "NO\n";
			} else {
				cout << "YES\n";
				shift = (shift + 1) % n;
			}
		}
	}


	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
