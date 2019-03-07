#pragma GCC optimize("Ofast")
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
#define NAME "buckets"
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
typedef unsigned int ui;

const int NN = 1e5;
const int N = (1 << 16);
ui cur = 0;
int n, a, b;
inline ui nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

inline ui nextRand32() {
	ui a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}

int cnt[N], begs[N];
ui arr[NN][2], buff[NN][2];
inline ull solver() {
	cin >> a >> b;
	for (int i = 0; i < n; ++i) {
		ui x = nextRand32();
		arr[i][0] = x >> 16;
		arr[i][1] = (x << 16) >> 16;
	}
	for (int i = 1; i >= 0; --i) {
		for (int j = 0; j < N; ++j) {
			cnt[j] = 0;
		}
		begs[0] = 0;
		for (int j = 0; j < n; ++j) {
			cnt[arr[j][i]]++;
		}
		for (int j = 1; j < N; ++j) {
			begs[j] = begs[j - 1] + cnt[j - 1];
		}
		for (int j = 0; j < n; ++j) {
			buff[begs[arr[j][i]]][0] = arr[j][0];
			buff[begs[arr[j][i]]][1] = arr[j][1];
			begs[arr[j][i]]++;
		}
		for (int j = 0; j < n; ++j) {
			arr[j][0] = buff[j][0];
			arr[j][1] = buff[j][1];
		}
	}
	ull sum = 0;
	for (int i = 0; i < n; ++i) {
		ui x = (arr[i][0] << 16) + arr[i][1];
		sum += (ull)(i + 1) * (ull)x;
	}
	return sum;
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

	int t;
	cin >> t >> n >> a >> b;
	for (int i = 0; i < t; ++i) {
		cout << solver() << "\n";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
