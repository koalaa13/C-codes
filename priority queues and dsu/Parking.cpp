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
#define NAME "parking"
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
int par[N];

int get(int v) {
	if (par[v] != v) {
		par[v] = get(par[v]);
	}
	return par[v];
}

void join(int v, int u) {
	v = get(v);
	u = get(u);
	if (v > u) {
		par[u] = v;
	} else {
		par[v] = u;
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

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		par[i] = i;
	}
	vector<bool> used(n);
	int j = 0;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		a--;
		a = get(a);
		if (a == n - 1) {
			if (used[n - 1]) {
				while (j < n && used[j]) {
					++j;
				}
				used[j] = 1;
				cout << j + 1 << " ";
				join(j, j + 1);
			} else {
				used[n - 1] = 1;
				cout << n << " ";
			}
		} else {
			used[a] = 1;
			cout << a + 1 << " ";
			join(a, a + 1);
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
