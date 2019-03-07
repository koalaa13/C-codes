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

#define F first
#define S second
#define mp make_pair
#define NAME "matrix"
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

const int INF = 2e9;

inline string sub(const string &a, const int &i, const int &j) {
	string res = "";
	for (int k = i; k < j; ++k) {
		res += a[k];
	}
	return res;
}

inline vector<int> calc_lcs(const string &a, const string &b) {
	int n = (int)a.size(), m = (int)b.size();
	vector<int> cur(m + 1), past(m + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i - 1] == b[j - 1]) {
				cur[j] = past[j - 1] + 1;
			} else {
				cur[j] = max(cur[j - 1], past[j]);
			}
		}
		past = cur;
	}
	return cur;
}

void rec(const string &a, const string &b) {
	if (a.size() == 1) {
		bool flag = 0;
		for (char c : b) {
			flag |= c == a[0];
		}
		if (flag) {
			cout << a[0];
		}
		return;
	}
	int mid = (int)a.size() / 2;
	string half1 = sub(a, 0, mid), half2 = sub(a, mid, (int)a.size());
	vector<int> lcs1 = calc_lcs(half1, b);
	string rev_b = b;
	reverse(rev_b.begin(), rev_b.end());
	string rev_half2 = half2;
	reverse(rev_half2.begin(), rev_half2.end());
	vector<int> lcs2 = calc_lcs(rev_half2, rev_b);
	int m = (int)b.size(), mx = -INF, ind = -1;
	for (int i = 0; i <= m; ++i) {
		if (mx < lcs1[i] + lcs2[m - i]) {
			mx = lcs1[i] + lcs2[m - i];
			ind = i;
		}
	}
	rec(half1, sub(b, 0, ind));
	rec(half2, sub(b, ind, m));
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

	string a, b;
	cin >> a >> b;
	rec(a, b);

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
