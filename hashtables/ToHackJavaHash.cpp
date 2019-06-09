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
#include <list>
#include <unordered_map>
// #pragma comment(linker, "/STACK:256000000")
using namespace std;

#define F first
#define S second
#define mp make_pair
#define NAME "map"
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

const int N = 1111;
const int p = 31;
int ps[N];
int get_hash(const string &s) {
	int hash = 0;
	for (size_t i = 0, j = s.length() - 1; i < s.length(); ++i, --j) {
		hash += (int)s[i] * ps[j];
	}
	return hash;
}

int main() {
#if _DEBUG
	// freopen("input.txt", "r", stdin);
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

	ps[0] = 1;
	ps[1] = p;
	for (int i = 2; i < N; ++i) {
		ps[i] = ps[i - 1] * p;
	}
	string s = "";
	for (int i = 0; i < 1000; ++i) {
		s += 'h';
	}
	vector<string> ss;
	ss.push_back(s);
	for (size_t i = 0; i < s.length() - 1; ++i) {
		s[i] = 'i';
		s[i + 1] = 'I';
		ss.push_back(s);
		s[i] = 'h';
		s[i + 1] = 'h';
	}
	int k;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		cout << ss[i] << "\n";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
