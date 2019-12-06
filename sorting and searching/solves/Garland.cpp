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
#define NAME "garland"
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
	cout.precision(2);
	cout.setf(ios::fixed);

	int n;
	ld a;
	cin >> n >> a;
	vector<ld> arr(n);
	arr[0] = a;
	ld l = 0, r = (ld)1e8;
	for (int it = 0; it < 64; ++it) {
		ld m = (l + r) / 2.;
		arr[1] = m;
		for (int i = 2; i < n; ++i) {
			arr[i] = 2. * arr[i - 1] - arr[i - 2] + 2.;
		}
		bool flag = 0;
		for (int i = 0; i < n; ++i) {
			flag |= arr[i] < 0.;
		}
		if (flag) {
			l = m;
		} else {
			r = m;
		}
	}
	arr[1] = l;
	for (int i = 2; i < n; ++i) {
		arr[i] = 2. * arr[i - 1] - arr[i - 2] + 2.;
	}
	cout << arr[n - 1];

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
