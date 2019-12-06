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
#define NAME "kth"
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

const int N = 3e7;
int n, k, A, B, C, arr[N], buff[N];

int kth_el(const int &k, const int &sz) {
	if (sz == 1) {
		return arr[0];
	}
	int ind = (rand() % sz), cnt_less = 0, cnt_eq = 0, cnt_greater = 0;
	for (int i = 0; i < sz; ++i) {
		if (i == ind) {
			continue;
		}
		cnt_less += arr[i] < arr[ind];
		cnt_eq += arr[i] == arr[ind];
		cnt_greater += arr[i] > arr[ind];
	}
	int cnt1 = 0, cnt2 = 0;
	for (; cnt_eq; cnt_eq--) {
		if (cnt_less > cnt_greater) {
			cnt_greater++;
			cnt1++;
		} else {
			cnt_less++;
			cnt2++;
		}
	}
	if (cnt_less == k - 1) {
		return arr[ind];
	}
	if (cnt_less >= k) {
		int j = 0;
		for (int i = 0; i < sz; ++i) {
			if (i == ind) {
				continue;
			}
			if (arr[i] < arr[ind]) {
				buff[j++] = arr[i];
			}
			if (arr[i] == arr[ind] && cnt2 > 0) {
				buff[j++] = arr[i];
				cnt2--;
			}
		}
		for (int i = 0; i < j; ++i) {
			arr[i] = buff[i];
		}
		return kth_el(k, j);
	} else {
		int j = 0;
		for (int i = 0; i < sz; ++i) {
			if (i == ind) {
				continue;
			}
			if (arr[i] > arr[ind]) {
				buff[j++] = arr[i];
			}
			if (arr[i] == arr[ind] && cnt1 > 0) {
				buff[j++] = arr[i];
				cnt1--;
			}
		}
		for (int i = 0; i < j; ++i) {
			arr[i] = buff[i];
		}
		return kth_el(k - cnt_less - 1, j);
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
	// srand((unsigned int)time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);

	cin >> n >> k >> A >> B >> C;
	for (int i = 0; i < 2; ++i) {
		cin >> arr[i];
	}
	for (int i = 2; i < n; ++i) {
		arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
	}
	cout << kth_el(k, n);

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
