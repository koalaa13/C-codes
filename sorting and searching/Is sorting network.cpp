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

inline bool is_sorted(const vector<int> &arr) {
	for (size_t i = 0; i + 1 < arr.size(); ++i) {
		if (arr[i] > arr[i + 1]) {
			return 0;
		}
	}
	return 1;
}

int main() {
#if SOLVE
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

	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<int, int>>> arr(k);
	for (int i = 0; i < k; ++i) {
		int q;
		cin >> q;
		for (int j = 0; j < q; ++j) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			arr[i].push_back({ min(a, b), max(a, b) });
		}
	}
	for (int mask = 0; mask < (1 << n); ++mask) {
		vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			if (mask & (1 << i)) {
				a[i] = 1;
			} else {
				a[i] = 0;
			}
		}
		for (size_t i = 0; i < arr.size(); ++i) {
			for (pair<int, int> comp : arr[i]) {
				if (a[comp.first] > a[comp.second]) {
					swap(a[comp.first], a[comp.second]);
				}
			}
		}
		if (!is_sorted(a)) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
