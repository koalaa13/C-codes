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
#define NAME "perm"
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

string conv(string s) {
	reverse(s.begin(), s.end());
	s += '#';
	reverse(s.begin(), s.end());
	return s;
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
	a = conv(a);
	b = conv(b);
	swap(a, b);
	int n = (int)a.size(), m = (int)b.size();
	vector<vector<bool>> dp(n, vector<bool>(m));
	dp[0][0] = 1;
	bool flag = 1;
	for (int i = 1; i < m; ++i) {
		flag &= b[i] == '*';
		dp[0][i] = flag;
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < m; ++j) {
			if (b[j] == '?') {
				dp[i][j] = dp[i - 1][j - 1];
				continue;
			}
			if (b[j] == '*') {
				dp[i][j] = dp[i - 1][j] | dp[i][j - 1];
				continue;
			}
			dp[i][j] = dp[i - 1][j - 1] & (a[i] == b[j]);
		}
	}
	if (dp[n - 1][m - 1]) {
		cout << "YES";
	} else {
		cout << "NO";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
