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
#define NAME "kbest"
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

typedef unsigned long long ull;
typedef float fl;
typedef long double ld;

const fl eps = (fl)1e-6;
const int N = 1e5;

struct dd {
	int ind;
	fl u, w;
};

dd arr[N], ll[N], rr[N];
inline bool cmp(const fl &mid, const dd &a, const dd &b) {
	return a.u - mid * a.w > b.u - mid * b.w;
}

inline void merge(const fl &mid, const int &l, const int &m, const int &r) {
	int nl = m - l, nr = r - m;
	for (int i = l; i < m; ++i) {
		ll[i - l] = arr[i];
	}
	for (int i = m; i < r; ++i) {
		rr[i - m] = arr[i];
	}
	for (int it = l, i = 0, j = 0; it < r; ++it) {
		if (i < nl && j < nr) {
			if (cmp(mid, ll[i], rr[j])) {
				arr[it] = ll[i++];
			} else {
				arr[it] = rr[j++];
			}
		} else {
			if (i < nl) {
				arr[it] = ll[i++];
			} else {
				arr[it] = rr[j++];
			}
		}
	}
}

void merge_sort(const fl &mid, const int &l, const int &r) {
	if (l + 1 != r) {
		int m = (l + r) >> 1;
		merge_sort(mid, l, m);
		merge_sort(mid, m, r);
		merge(mid, l, m, r);
	}
}
int n, k;
inline bool check(const fl &mid) {
	fl can = 0.;
	merge_sort(mid, 0, n);
	for (int i = 0; i < k; ++i) {
		can += arr[i].u - mid * arr[i].w;
	}
	return can >= 0.;
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

	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i].u >> arr[i].w;
		arr[i].ind = i + 1;
	}
	fl l = 0, r = (fl)1e7;
	int it = 0;
	while (r - l > eps && it < 47) {
		fl m = (l + r) / (fl)2.;
		if (check(m)) {
			l = m;
		} else {
			r = m;
		}
		++it;
	}
	if (check(r)) {
		for (int i = 0; i < k; ++i) {
			cout << arr[i].ind << " ";
		}
		return 0;
	}
	merge_sort(l, 0, n);
	for (int i = 0; i < k; ++i) {
		cout << arr[i].ind << " ";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
