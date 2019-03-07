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
#define NAME "binsearch"
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

int bs(int val, const vector<int> &arr) {
	size_t l = 0, r = arr.size();
	while (r - l > 1) {
		size_t m = (l + r) / 2;
		if (arr[m] > val) {
			r = m;
		} else {
			l = m;
		}
	}
	return (int)l;
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
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		int ind = bs(v, arr);
		if (arr[ind] != v) {
			cout << "-1 -1\n";
		} else {
			int ind1 = bs(v - 1, arr);
			if (arr[ind1] != v) {
				++ind1;
			}
			cout << ind1 + 1 << " " << ind + 1 << "\n";
		}
	}


	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
