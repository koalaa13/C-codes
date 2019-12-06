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

vector<int> merge_sort(int l, int r, const vector<int> &arr) {
	if (r - l == 1) {
		return{ arr[l] };
	}
	int m = (l + r) / 2;
	vector<int> res_l = merge_sort(l, m, arr);
	vector<int> res_r = merge_sort(m, r, arr);
	size_t nl = res_l.size(), nr = res_r.size();
	vector<int> res(nl + nr);
	for (size_t it = 0, i = 0, j = 0; it < res.size(); ++it) {
		if (i < nl && j < nr) {
			if (res_l[i] < res_r[j]) {
				res[it] = res_l[i++];
			} else {
				res[it] = res_r[j++];
			}
		} else {
			if (i < nl) {
				res[it] = res_l[i++];
			} else {
				res[it] = res_r[j++];
			}
		}
	}
	return res;
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

	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	vector<int> sorted = merge_sort(0, n, arr);
	for (int i : sorted) {
		cout << i << " ";
	}


	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
